#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <cmath>
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

struct PartyData
{
	Thread** thread ;
	Party* party ;
	Mutex* p_mutex ;
} ;

void manage_client ( void* data )
{
	
	// On récupère les données
	ClientData* cli_data = static_cast < ClientData* > ( data ) ;
	
	// Boucle pour répondre au client
	bool quit = false ;
	while ( ! quit )
	{
		
		/* Traitement à faire pour répondre au client */
		
		quit = true ;
		
	}
	
	// Déconnexion du client
	std::cout << "Déconnexion du client : " << (*cli_data->client)->second << std::endl ;
	(*cli_data->client)->first.Close ( ) ;
	
	// Libération de la mémoire
	delete (*cli_data->client) ;
	(*cli_data->client) = NULL ;
	
	delete (*cli_data->thread) ;
	(*cli_data->thread) = NULL ;
	
	delete cli_data ;
	
}

void manage_party ( void* data )
{
	
	// On récupère les données
	PartyData* party_data = static_cast < PartyData* > ( data ) ;
	party_data->party->setMessage ( "En attente d'autres joueurs" ) ;
	
	// On déclare les varibles pour gérer le temps
	Clock clk ;
	float last_update = 0.f ;
	float now ;
	
	// Boucle de mise à jour de la partie
	while ( party_data->party->getStatus ( ) != Party::ENDED )
	{
		
		// On bloque l'accès à la partie
		party_data->p_mutex->Lock ( ) ;
		now = clk.GetElapsedTime ( ) ;
		
		// On fait les traitement nécessaire
		// Si la partie est en cours
		if ( party_data->party->getStatus ( ) == Party::PLAYING )
		{
			
			std::pair < unsigned char, Character* > chars = party_data->party->getChars ( ) ;
			
			// On parcourt la liste des personnages
			for ( unsigned char i = 0 ; i < chars.first ; i ++ )
			{
				
				// On déplace le personnage par tranche de 50 ms + gestion des collissions avec les murs ~ normalement terminé
				for ( float j = 0.050f ; j < now - last_update ; j += 0.050f )
				{
					
					unsigned char
							wish = chars.second[i].getWish ( ),
							moving = chars.second[i].getMoving ( ) ;
					
					// Peut-il aller au nord ?
					if ( party_data->party->getCase ( static_cast < unsigned char > ( chars.second[i].getX ( ) ), static_cast < unsigned char > ( chars.second[i].getY ( ) - 0.1f ) ) != Party::WALL )
					{
						
						// Si c'est son souhait, on le réalise
						if ( wish == Character::NORTH )
						{
							
							chars.second[i].setY ( chars.second[i].getY ( ) - 0.1f ) ;
							chars.second[i].setMoving ( wish ) ;
							chars.second[i].setWish ( moving ) ;
							
						}
						// Ou si c'est sa direction actuelle, il continue
						else if ( moving == Character::NORTH )
							chars.second[i].setY ( chars.second[i].getY ( ) - 0.1f ) ;
						
					}
					// Ou peut-il aller au sud ?
					else if ( party_data->party->getCase ( static_cast < unsigned char > ( chars.second[i].getX ( ) ), static_cast < unsigned char > ( chars.second[i].getY ( ) + 1.1f ) ) != Party::WALL )
					{
						
						// Si c'est son souhait, on le réalise
						if ( wish == Character::SOUTH )
						{
							
							chars.second[i].setY ( chars.second[i].getY ( ) + 0.1f ) ;
							chars.second[i].setMoving ( wish ) ;
							chars.second[i].setWish ( moving ) ;
							
						}
						// Ou si c'est sa direction actuelle, il continue
						else if ( moving == Character::SOUTH )
							chars.second[i].setY ( chars.second[i].getY ( ) + 0.1f ) ;
						
					}
					// Peut-il aller à l'ouest ?
					else if ( party_data->party->getCase ( static_cast < unsigned char > ( chars.second[i].getX ( ) - 0.1f ), static_cast < unsigned char > ( chars.second[i].getY ( ) ) ) != Party::WALL )
					{
						
						// Si c'est son souhait, on le réalise
						if ( wish == Character::WEST )
						{
							
							chars.second[i].setX ( chars.second[i].getX ( ) - 0.1f ) ;
							chars.second[i].setMoving ( wish ) ;
							chars.second[i].setWish ( moving ) ;
							
						}
						// Ou si c'est sa direction actuelle, il continue
						else if ( moving == Character::WEST )
							chars.second[i].setX ( chars.second[i].getX ( ) - 0.1f ) ;
						
					}
					// Ou peut-il aller à l'est ?
					else if ( party_data->party->getCase ( static_cast < unsigned char > ( chars.second[i].getX ( ) + 1.1f ), static_cast < unsigned char > ( chars.second[i].getY ( ) ) ) != Party::WALL )
					{
						
						// Si c'est son souhait, on le réalise
						if ( wish == Character::SOUTH )
						{
							
							chars.second[i].setX ( chars.second[i].getX ( ) + 0.1f ) ;
							chars.second[i].setMoving ( wish ) ;
							chars.second[i].setWish ( moving ) ;
							
						}
						// Ou si c'est sa direction actuelle, il continue
						else if ( moving == Character::SOUTH )
							chars.second[i].setX ( chars.second[i].getX ( ) + 0.1f ) ;
						
					}
					
				} // Déplacement du personnage + gestion des collisions avec les murs
				
				// On regarde si le personnage est entrée en collission avec un autre ~ reste le respawn
				for ( unsigned char j = i + 1 ; j < chars.first ; j ++ )
				{
					
					// Si c'est bien un autre personnage et qu'il y a collision
					if ( j != i && abs ( chars.second[i].getY ( ) - chars.second[j].getY ( ) ) < 1.f && abs ( chars.second[i].getX ( ) - chars.second[j].getX ( ) ) < 1.f )
					{
						
						// i se fait manger, respawn en fantôme et j devient le pacman
						if ( chars.second[i].getStatus ( ) == Character::PACMAN && chars.second[j].getStatus ( ) == Character::GHOST )
						{
							
							chars.second[i].setStatus ( Character::GHOST ) ;
							chars.second[j].setStatus ( Character::PACMAN ) ;
							
							// ~ Respawn du personnage i
							
						}
						// l'inverse
						else if ( chars.second[i].getStatus ( ) == Character::GHOST && chars.second[j].getStatus ( ) == Character::PACMAN )
						{
							
							chars.second[j].setStatus ( Character::GHOST ) ;
							chars.second[i].setStatus ( Character::PACMAN ) ;
							
							// ~ Respawn du personnage j
							
						}
						// i est un fantôme mais ce fait manger par j, super pacman
						else if ( chars.second[i].getStatus ( ) == Character::GHOST && chars.second[j].getStatus ( ) == Character::SUPER_PACMAN )
						{
							
							chars.second[j].setPoint ( chars.second[j].getPoint ( ) + 100 ) ;
							
							// ~ Respawn du personnage i
							
						}
						// l'inverse
						else if ( chars.second[i].getStatus ( ) == Character::SUPER_PACMAN && chars.second[j].getStatus ( ) == Character::GHOST )
						{
							
							chars.second[i].setPoint ( chars.second[i].getPoint ( ) + 100 ) ;
							
							// ~ Respawn du personnage j
							
						}
						
					}
					
				} // Collisions avec les autres personnages
				
				// On regarde si le personnage peut manger des points ~ reste le timer du super pac man
				if ( chars.second[i].getStatus ( ) == Character::PACMAN || chars.second[i].getStatus ( ) == Character::SUPER_PACMAN )
				{
					
					float
						x = chars.second[i].getX ( ),
						y = chars.second[i].getY ( ) ;
					
					if ( x == floor ( x ) && y == floor ( y ) )
					{
						
						if ( party_data->party->getCase ( static_cast < unsigned char > ( x ), static_cast < unsigned char > ( y ) ) == Party::PAC_POINT )
						{
							
							chars.second[i].setPoint ( chars.second[i].getPoint ( ) + 10 ) ;
							
						}
						else if ( party_data->party->getCase ( static_cast < unsigned char > ( x ), static_cast < unsigned char > ( y ) ) == Party::SUPERPAC_POINT )
						{
							
							chars.second[i].setPoint ( chars.second[i].getPoint ( ) + 50 ) ;
							chars.second[i].setStatus ( Character::SUPER_PACMAN ) ;
							// ~ lancer le timer du super pacman
							
						}
						
					}
					
				} // Collision avec les points
				
			} // Parcourt de la liste des personnages
			
		} // Partie en cours
		else if ( party_data->party->getStatus ( ) == Party::WAITING )
		{
			
			
			
		} // Partie en attente
		
		// Débloque l'accès à la partie
		last_update = now ;
		party_data->p_mutex->Unlock ( ) ;
		
		// On patiente 20 ms
		Sleep ( 0.020f ) ;
		
	} // Boucle mise à jour de la partie
	
	// Libération de la mémoire
	delete (*party_data->thread) ;
	(*party_data->thread) = NULL ;
	
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
	
	// On crée la partie, son mutex et son thread
	std::cout << "Création de la partie" << std::endl ;
	Party party ( map_path, 180.f, slot ) ;
	Mutex p_mutex ;
	Thread** p_thread = new Thread* ;
	
	if ( party.getMapName ( ) == "" )
	{
		
		std::cout << "Impossible de charger la carte" << std::endl ;
		exit ( 1 ) ;
		
	}
	
	PartyData* p_data = new PartyData ;
	p_data->thread = p_thread ;
	p_data->party = &party ;
	p_data->p_mutex = &p_mutex ;
	*p_thread = new Thread ( manage_party, static_cast < void* > ( p_data ) ) ;
	
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
	std::pair < SocketTCP, IPAddress >* new_client = NULL ;
	// Tant que la partie n'est pas terminée
	while ( party.getStatus ( ) != Party::ENDED )
	{
		
		if ( new_client == NULL )
			new_client = new std::pair < SocketTCP, IPAddress > ;
		
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
				
				std::cout << "Client " << new_client->second << " associé au thread " << id << std::endl ;
				threads[id] = new Thread ( manage_client, static_cast < void* > ( cli_data ) ) ;
				threads[id]->Launch ( ) ;
				
				new_client = NULL ;
				
			}
			
		}
		else
		{
			
			Sleep ( 0.25f ) ;
			
		}
		
	} // Boucle d'écoute
	
	// Libération de la mémoire
	for ( unsigned char i = 0 ; i < slot ; i ++ )
	{
		
		delete threads[i] ;
		delete clients[i] ;
		
	}
	
	delete[] threads ;
	delete[] clients ;
	delete new_client ;
	delete p_thread ;
	
	return EXIT_SUCCESS ;
	
}
