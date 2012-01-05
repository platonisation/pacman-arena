#include <cstdlib>
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace sf ;

class Party { public : bool getEnded ( ) { return false ; } } ;

struct ClientData
{
	int id ;
	SocketTCP* sck ;
	IPAddress* addr ;
	Party* party ;
	Mutex* p_mutex ;
} ;

void manage_client ( void* data )
{
	
	
	
}

int main ( int argc, char *argv[] )
{
	
	int
		slot,
		slot_in_use = 0 ;
	
	// Si on a le bon nombre de paramètres
	if ( argc == 2 )
	{
		
		// On récupère les paramètres
		slot = atoi ( argv[1] ) ;
		
		// On vérifie la validité des paramètres
		if ( slot < 1 || slot > 4 )
		{
			
			std::cout << "Nombre de slot invalide" << std::endl ;
			exit ( 1 ) ;
			
		}
		
	}
	else
	{
		
		std::cout << "Utilisation : " << argv[0] << " [nb_slot]" << std::endl ;
		exit ( 1 ) ;
		
	}
	
	// On crée la partie et son mutex
	Party party ;
	Mutex p_mutex ;
	
	// On alloue les sockets pour les clients et différentes variables associées
	SocketTCP* clients = new SocketTCP[slot] ;
	IPAddress* cli_addr = new IPAddress[slot] ;
	bool* used_socket = new bool[slot] ;
	Thread** cli_thread = new Thread*[slot] ;
	
	SocketTCP listener ;
	if ( ! listener.Listen ( 8910 ) )
	{
		
		std::cout << "Impossible d'ouvrir le listener" << std::endl ;
		delete[] clients ;
		exit ( 1 ) ;
		
	}
	
	// Tant que la partie n'est pas terminée
	while ( ! party.getEnded ( ) )
	{
		
		// S'il reste des slots de libre
		if ( slot_in_use < slot )
		{
			
			int sck_nbr ;
			
			// On sait qu'il y en a de libre, on en cherche un
			for ( int i = 0 ; i < slot ; i ++ )
			{
				
				// Si le socket courant est libre, on va l'utiliser
				if ( ! used_socket[i] )
				{
					
					sck_nbr = i ;
					break ;
					
				}
				
			}
			
			if ( listener.Accept ( clients[sck_nbr], &cli_addr[sck_nbr] ) != Socket::Done )
			{
				
				std::cout << "Impossible de recevoir le client : " << cli_addr << std::endl ;
				
			}
			else
			{
				
				ClientData* cli_data = new ClientData ( ) ;
				cli_data->id = sck_nbr ;
				cli_data->sck = &clients[sck_nbr] ;
				cli_data->addr = &cli_addr[sck_nbr] ;
				cli_data->party = &party ;
				cli_data->p_mutex = &p_mutex ;
				
				cli_thread[sck_nbr] = new Thread ( manage_client, static_cast<void*> ( cli_data ) ) ;
				
				cli_thread[sck_nbr]->Launch ( ) ;
				
			}
			
		} // S'il restait de la place
		
		Sleep ( 0.5f ) ;
		
	} // Boucle d'écoute
	
	delete[] clients ;
	
	return EXIT_SUCCESS ;
	
}
