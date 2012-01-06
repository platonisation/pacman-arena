#include <cstdlib>
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace sf ;

class Party { public : bool getEnded ( ) { return false ; } } ;

struct ClientData
{
	int id ;
	bool* working ;
	SocketTCP* sck ;
	IPAddress* addr ;
	Party* party ;
	Mutex* p_mutex ;
} ;

void manage_client ( void* data )
{
	
	ClientData* cli_data = static_cast<ClientData*> ( data ) ;
	
	std::cout << "Prise en charge du client : " << *cli_data->addr << std::endl ;
	cli_data->sck->Send ( "000 Hi\n", sizeof ( "000 Hi\n" ) ) ;
	
	Sleep ( 2.f ) ;
	
	cli_data->sck->Send ( "999 Bye\n", sizeof ( "999 Bye\n" ) ) ;
	cli_data->sck->Close ( ) ;
	std::cout << "Déconnexion du client : " << *cli_data->addr << std::endl ;
	
	*cli_data->working = false ;
	
}

int main ( int argc, char *argv[] )
{
	
	int slot ;
	
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
	std::cout << "Création de la partie" << std::endl ;
	Party party ;
	Mutex p_mutex ;
	
	// On alloue les sockets pour les clients et différentes variables associées
	std::cout << "Création des sockets accueillant les clients" << std::endl ;
	SocketTCP* clients = new SocketTCP[slot] ;
	IPAddress* cli_addr = new IPAddress[slot] ;
	bool* used_socket = new bool[slot] ;
	Thread** cli_thread = new Thread*[slot] ;
	
	for ( int i = 0 ; i < slot ; i ++ )
	{
		
		used_socket[i] = false ;
		cli_thread[i] = NULL ;
		
	}
	
	std::cout << "Création du socket listener" << std::endl ;
	SocketTCP listener ;
	if ( ! listener.Listen ( 8910 ) )
	{
		
		std::cout << "Impossible d'ouvrir le listener" << std::endl ;
		exit ( 1 ) ;
		
	}
	
	std::cout << "Démarrage de l'écoute" << std::endl ;
	// Tant que la partie n'est pas terminée
	while ( ! party.getEnded ( ) )
	{
		
		int slot_in_use = 0 ;
		for ( int i = 0 ; i < slot ; i ++ )
		{
			
			// Calcul du nombre de place restante
			if ( used_socket[i] )
				slot_in_use ++ ;
			// Sinon on vérifie le thread pour le déallouer si besoin
			else
				if ( cli_thread[i] != NULL )
					delete cli_thread[i] ;
			
		}
		
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
				cli_data->working = &used_socket[sck_nbr] ;
				cli_data->sck = &clients[sck_nbr] ;
				cli_data->addr = &cli_addr[sck_nbr] ;
				cli_data->party = &party ;
				cli_data->p_mutex = &p_mutex ;
				
				cli_thread[sck_nbr] = new Thread ( manage_client, static_cast<void*> ( cli_data ) ) ;
				
				cli_thread[sck_nbr]->Launch ( ) ;
				
			}
			
		} // S'il restait de la place
		// Sinon on attend quelque temps
		else
		{
			
			Sleep ( 0.5f ) ;
			
		}
		
	} // Boucle d'écoute
	
	delete[] clients ;
	delete[] cli_addr ;
	delete[] used_socket ;
	delete[] cli_thread ;
	
	return EXIT_SUCCESS ;
	
}
