#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Party.h"

using namespace sf ;

struct ClientData
{
	unsigned char id ;
	unsigned char slot ;
	std::pair < SocketTCP, IPAddress >** client ;
	Thread** thread ;
	Party* party ;
	Mutex* p_mutex ;
} ;

void manage_client ( void* data )
{
	
	ClientData* cli_data = static_cast < ClientData* > ( data ) ;
	
	// (*cli_data->client)->first.Send ( "Hi\n", sizeof ( "Hi\n" ) ) ;
	
	Sleep ( 2.f ) ;
	
	std::cout << "Déconnexion du client : " << (*cli_data->client)->second << std::endl ;
	(*cli_data->client)->first.Close ( ) ;
	
	delete cli_data ;
	
	delete (*cli_data->client) ;
	(*cli_data->client) = NULL ;
	
	delete (*cli_data->thread) ;
	(*cli_data->thread) = NULL ;
	
}

int main ( int argc, char *argv[] )
{
	
	unsigned char slot ;
	std::string map_path ;
	
	// Si on a le bon nombre de paramètres
	if ( argc == 3 )
	{
		
		// On récupère les paramètres
		slot = atoi ( argv[1] ) ;
		map_path = argv[2] ;
		
		// On vérifie la validité des paramètres
		if ( slot < 1 || slot > 4 )
		{
			
			std::cout << "Nombre de slot invalide" << std::endl ;
			exit ( 1 ) ;
			
		}
		
		std::ifstream fichier ( map_path.c_str ( ) ) ;
    	if ( fichier.fail ( ) )
    		map_path = "maps/default.pacmap" ;
		
		
	}
	else
	{
		
		std::cout << "Utilisation : " << argv[0] << " [slot_number] [map_path]" << std::endl ;
		exit ( 1 ) ;
		
	}
	
	// On crée la partie et son mutex
	std::cout << "Création de la partie" << std::endl ;
	Party party ( map_path, 180.f, slot ) ;
	Mutex p_mutex ;
	
	// On alloue les sockets pour les clients et différentes variables associées
	std::cout << "Création des sockets accueillant les clients" << std::endl ;
	std::pair < SocketTCP, IPAddress >** clients = new std::pair < SocketTCP, IPAddress >*[slot]  ;
	Thread** threads = new Thread*[slot] ;
	
	for ( int i = 0 ; i < slot ; i ++ )
	{
		
		clients[i] = NULL ;
		threads[i] = NULL ;
		
	}
	
	std::cout << "Création du socket listener" << std::endl ;
	SocketTCP listener ;
	listener.SetBlocking ( false ) ;
	if ( ! listener.Listen ( 8910 ) )
	{
		
		std::cout << "Impossible d'ouvrir le listener" << std::endl ;
		exit ( 1 ) ;
		
	}
	
	std::cout << "Démarrage de l'écoute" << std::endl ;
	// Tant que la partie n'est pas terminée
	while ( party.getStatus ( ) != Party::ENDED )
	{
		
		std::pair < SocketTCP, IPAddress >* new_client = new std::pair < SocketTCP, IPAddress > ;
		
		if ( listener.Accept ( new_client->first, &new_client->second ) == Socket::Done )
		{
			
			// On récupère un id libre
			unsigned char id = 255 ;
			for ( unsigned char i = 0 ; i < slot ; i ++ )
				if ( clients[i] == NULL )
				{
					id = i ;
					break ;
				}
			
			// Si le serveur est plein (on n'a pas trouvé d'id)
			if ( id == 255 )
			{
				
				std::cout << "Refus du client : " << new_client->second << " (Serveur plein)" << std::endl ;
				new_client->first.Send ( "0", sizeof ( "0" ) ) ;
				new_client->first.Close ( ) ;
				
			}
			// Sinon on prend en charge le client
			else
			{
				
				std::cout << "Prise en charge du client : " << new_client->second << std::endl ;
				new_client->first.Send ( "1", sizeof ( "1" ) ) ;
				clients[id] = new_client ;
				
				ClientData* cli_data = new ClientData ;
				
				cli_data->id = id ;
				cli_data->client = &clients[id] ;
				cli_data->thread = &threads[id] ;
				cli_data->party = &party ;
				cli_data->p_mutex = &p_mutex ;
				
				threads[id] = new Thread ( manage_client, static_cast < void* > ( cli_data ) ) ;
				threads[id]->Launch ( ) ;
				
			}
			
		}
		else
		{
			
			Sleep ( 0.5f ) ;
			
		}
		
	} // Boucle d'écoute
	
	for ( unsigned char i = 0 ; i < slot ; i ++ )
	{
		
		delete threads[i] ;
		delete clients[i] ;
		
	}
	
	delete[] threads ;
	delete[] clients ;
	
	return EXIT_SUCCESS ;
	
}
