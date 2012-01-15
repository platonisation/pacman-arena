#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>
#include <cmath>
#include <ctime>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Party.h"
#include "network.h"

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
	
	// On crée le personnage du client
	cli_data->p_mutex->Lock ( ) ;
	Character** chars = cli_data->party->getChars ( ) ;
	chars[cli_data->id] = new Character ;
	
	std::pair < unsigned char, std::pair < unsigned char, unsigned char >* > spawns = cli_data->party->getSpawns ( ) ;
	unsigned char nb = rand ( ) % spawns.first ;
	
	chars[cli_data->id]->setX ( static_cast < float > ( spawns.second[nb].first ) ) ;
	chars[cli_data->id]->setY ( static_cast < float > ( spawns.second[nb].second ) ) ;
	cli_data->p_mutex->Unlock ( ) ;
	
	// Boucle pour répondre au client
	bool quit = false ;
	while ( ! quit )
	{
		
		cli_data->p_mutex->Lock ( ) ;
		std::cout << "Obtention du mutex pour le client : [" << static_cast < int > ( cli_data->id ) << "] " << (*cli_data->client)->second << std::endl ;
		
		if ( cli_data->party->getStatus ( ) == Party::ENDED )
			quit = true ;
		
		// Envoie de données
		Packet pck_to_send ;
		pck_to_send << std::string ( "Data" ) << ( *cli_data->party ) ;
		
		(*cli_data->client)->first.Send ( pck_to_send ) ;
		std::cout << "Envoie de données pour le client : [" << static_cast < int > ( cli_data->id ) << "] " << (*cli_data->client)->second << std::endl ;
		
		// Réception des données
		Packet pck_to_receive ;
		(*cli_data->client)->first.Receive ( pck_to_receive ) ;
		
		std::string client_cmd ;
		pck_to_receive >> client_cmd ;
		std::cout << "Réception de données du client : [" << static_cast < int > ( cli_data->id ) << "] " << (*cli_data->client)->second << std::endl ;
		
		if ( client_cmd == "Quit" )
		{
			
			delete chars[cli_data->id] ;
			chars[cli_data->id] = NULL ;
			quit = true ;
			
		}
		else if ( client_cmd == "Movement" )
		{
			
			unsigned char mvt1, mvt2 ;
			pck_to_receive >> mvt1 >> mvt2 ;
			
			if ( mvt1 == chars[cli_data->id]->getMoving ( ) )
				chars[cli_data->id]->setWish ( mvt2 ) ;
			else if ( mvt2 == chars[cli_data->id]->getMoving ( ) )
				chars[cli_data->id]->setWish ( mvt1 ) ;
			else
			{
				
				chars[cli_data->id]->setMoving ( mvt1 ) ;
				chars[cli_data->id]->setWish ( mvt2 ) ;
				
			}
			
		}
		
		cli_data->p_mutex->Unlock ( ) ;
		
		Sleep ( 0.050f ) ;
		
	}
	
	// Déconnexion du client
	std::cout << "Déconnexion du client : [" << static_cast < int > ( cli_data->id ) << "] " << (*cli_data->client)->second << std::endl ;
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
	party_data->party->setMessage ( "Partie en attente d'autres joueurs !" ) ;
	
	// On déclare les varibles pour gérer le temps
	Clock clk ;
	float last_update = 0.f ;
	float now ;
	bool scoring = false ;
	
	// Boucle de mise à jour de la partie
	while ( party_data->party->getStatus ( ) != Party::ENDED )
	{
		
		now = clk.GetElapsedTime ( ) ;
		
		// Si ça fait 50 ms, on met à jour la partie
		if ( 0.050f < now - last_update )
		{
			
			// On bloque l'accès à la partie
			party_data->p_mutex->Lock ( ) ;
			
			// On fait les traitements nécessaires
			// Si la partie est en cours
			// ~ normalement terminé
			// - reste à vérifier la gestion du souhait de déplacement et de l'orientation du personnage
			if ( party_data->party->getStatus ( ) == Party::PLAYING )
			{
				
				party_data->party->setTimer ( 180.f - now ) ;
				Character** chars = party_data->party->getChars ( ) ;
				
				// Temps écoulés
				if ( now > 180.f )
				{
					
					scoring = true ;
					clk.Reset ( ) ;
					now = 0.f ;
					
					std::ostringstream msg ;
					msg << "Partie terminée !" << std::endl << "Score :" << std::endl ;
					
					for ( unsigned char i = 0 ; i < party_data->party->getSlot ( ) ; i ++ )
					{
						
						// Si le personnage i existe
						if ( chars[i] != NULL )
						{
							
							msg << " - " << chars[i]->getName ( ) << " : " << chars[i]->getPoint ( ) << std::endl ;
							
						}
						
					}
					
					party_data->party->setMessage ( msg.str ( ) ) ;
					party_data->party->setStatus ( Party::WAITING ) ;
					
				} // Temps écoulés
				// La partie continue
				else
				{
					
					bool pacman_spawn = false ;
					
					// On parcourt la liste des personnages
					for ( unsigned char i = 0 ; i < party_data->party->getSlot ( ) ; i ++ )
					{
						
						// Si le personnage i existe
						if ( chars[i] != NULL )
						{
						
							// On déplace le personnage par tranche de 50 ms + gestion des collissions avec les murs
							// ~ reste à vérifier la gestion du souhait de déplacement et de l'orientation du personnage
							for ( float j = 0.050f ; j < now - last_update ; j += 0.050f )
							{
								
								unsigned char
										wish = chars[i]->getWish ( ),
										moving = chars[i]->getMoving ( ) ;
								
								// Peut-il aller au nord ?
								if ( party_data->party->getCase ( static_cast < unsigned char > ( chars[i]->getX ( ) ), static_cast < unsigned char > ( chars[i]->getY ( ) - 0.1f ) ) != Party::WALL )
								{
									
									// Si c'est son souhait, on le réalise
									if ( wish == Character::NORTH )
									{
										
										chars[i]->setY ( chars[i]->getY ( ) - 0.1f ) ;
										chars[i]->setMoving ( wish ) ;
										chars[i]->setWish ( moving ) ;
										
									}
									// Ou si c'est sa direction actuelle, il continue
									else if ( moving == Character::NORTH )
										chars[i]->setY ( chars[i]->getY ( ) - 0.1f ) ;
									
								}
								// Ou peut-il aller au sud ?
								else if ( party_data->party->getCase ( static_cast < unsigned char > ( chars[i]->getX ( ) ), static_cast < unsigned char > ( chars[i]->getY ( ) + 1.1f ) ) != Party::WALL )
								{
									
									// Si c'est son souhait, on le réalise
									if ( wish == Character::SOUTH )
									{
										
										chars[i]->setY ( chars[i]->getY ( ) + 0.1f ) ;
										chars[i]->setMoving ( wish ) ;
										chars[i]->setWish ( moving ) ;
										
									}
									// Ou si c'est sa direction actuelle, il continue
									else if ( moving == Character::SOUTH )
										chars[i]->setY ( chars[i]->getY ( ) + 0.1f ) ;
									
								}
								// Peut-il aller à l'ouest ?
								else if ( party_data->party->getCase ( static_cast < unsigned char > ( chars[i]->getX ( ) - 0.1f ), static_cast < unsigned char > ( chars[i]->getY ( ) ) ) != Party::WALL )
								{
									
									// Si c'est son souhait, on le réalise
									if ( wish == Character::WEST )
									{
										
										chars[i]->setX ( chars[i]->getX ( ) - 0.1f ) ;
										chars[i]->setMoving ( wish ) ;
										chars[i]->setWish ( moving ) ;
										
									}
									// Ou si c'est sa direction actuelle, il continue
									else if ( moving == Character::WEST )
										chars[i]->setX ( chars[i]->getX ( ) - 0.1f ) ;
									
								}
								// Ou peut-il aller à l'est ?
								else if ( party_data->party->getCase ( static_cast < unsigned char > ( chars[i]->getX ( ) + 1.1f ), static_cast < unsigned char > ( chars[i]->getY ( ) ) ) != Party::WALL )
								{
									
									// Si c'est son souhait, on le réalise
									if ( wish == Character::SOUTH )
									{
										
										chars[i]->setX ( chars[i]->getX ( ) + 0.1f ) ;
										chars[i]->setMoving ( wish ) ;
										chars[i]->setWish ( moving ) ;
										
									}
									// Ou si c'est sa direction actuelle, il continue
									else if ( moving == Character::SOUTH )
										chars[i]->setX ( chars[i]->getX ( ) + 0.1f ) ;
									
								}
								
							} // Déplacement du personnage + gestion des collisions avec les murs
							
							// On regarde si le personnage est entrée en collission avec un autre
							// ~ normalement terminé - à tester
							for ( unsigned char j = i + 1 ; j < party_data->party->getSlot ( ) ; j ++ )
							{
								
								// Si c'est bien un autre personnage et qu'il y a collision
								if ( j != i && chars[j] != NULL && abs ( chars[i]->getY ( ) - chars[j]->getY ( ) ) < 1.f && abs ( chars[i]->getX ( ) - chars[j]->getX ( ) ) < 1.f )
								{
									
									// i se fait manger, respawn en fantôme et j devient le pacman
									if ( chars[i]->getStatus ( ) == Character::PACMAN && chars[j]->getStatus ( ) == Character::GHOST )
									{
										
										chars[i]->setStatus ( Character::GHOST ) ;
										chars[j]->setStatus ( Character::PACMAN ) ;
										
										// Respawn du personnage i
										std::pair < unsigned char, std::pair < unsigned char, unsigned char >* > spawns = party_data->party->getSpawns ( ) ;
										unsigned char nb = rand ( ) % spawns.first ;
										
										chars[i]->setX ( spawns.second[nb].first ) ;
										chars[i]->setY ( spawns.second[nb].second ) ;
										
									}
									// l'inverse
									else if ( chars[i]->getStatus ( ) == Character::GHOST && chars[j]->getStatus ( ) == Character::PACMAN )
									{
										
										chars[j]->setStatus ( Character::GHOST ) ;
										chars[i]->setStatus ( Character::PACMAN ) ;
										
										// Respawn du personnage j
										std::pair < unsigned char, std::pair < unsigned char, unsigned char >* > spawns = party_data->party->getSpawns ( ) ;
										unsigned char nb = rand ( ) % spawns.first ;
										
										chars[j]->setX ( spawns.second[nb].first ) ;
										chars[j]->setY ( spawns.second[nb].second ) ;
										
									}
									// i est un fantôme mais ce fait manger par j, super pacman
									else if ( chars[i]->getStatus ( ) == Character::GHOST && chars[j]->getStatus ( ) == Character::SUPER_PACMAN )
									{
										
										chars[j]->setPoint ( chars[j]->getPoint ( ) + 100 ) ;
										
										// Respawn du personnage i
										std::pair < unsigned char, std::pair < unsigned char, unsigned char >* > spawns = party_data->party->getSpawns ( ) ;
										unsigned char nb = rand ( ) % spawns.first ;
										
										chars[i]->setX ( spawns.second[nb].first ) ;
										chars[i]->setY ( spawns.second[nb].second ) ;
										
									}
									// l'inverse
									else if ( chars[i]->getStatus ( ) == Character::SUPER_PACMAN && chars[j]->getStatus ( ) == Character::GHOST )
									{
										
										chars[i]->setPoint ( chars[i]->getPoint ( ) + 100 ) ;
										
										// Respawn du personnage j
										std::pair < unsigned char, std::pair < unsigned char, unsigned char >* > spawns = party_data->party->getSpawns ( ) ;
										unsigned char nb = rand ( ) % spawns.first ;
										
										chars[j]->setX ( spawns.second[nb].first ) ;
										chars[j]->setY ( spawns.second[nb].second ) ;
										
									}
									
								}
								
							} // Collisions avec les autres personnages
							
							// On regarde si le personnage peut manger des points
							// ~ normalement terminé - à tester
							if ( chars[i]->getStatus ( ) == Character::PACMAN || chars[i]->getStatus ( ) == Character::SUPER_PACMAN )
							{
								
								pacman_spawn = true ;
								
								float
									x = chars[i]->getX ( ),
									y = chars[i]->getY ( ) ;
								
								if ( x == floor ( x ) && y == floor ( y ) )
								{
									
									if ( party_data->party->getCase ( static_cast < unsigned char > ( x ), static_cast < unsigned char > ( y ) ) == Party::PAC_POINT )
									{
										
										chars[i]->setPoint ( chars[i]->getPoint ( ) + 10 ) ;
										
									}
									else if ( party_data->party->getCase ( static_cast < unsigned char > ( x ), static_cast < unsigned char > ( y ) ) == Party::SUPERPAC_POINT )
									{
										
										chars[i]->setPoint ( chars[i]->getPoint ( ) + 50 ) ;
										chars[i]->setStatus ( Character::SUPER_PACMAN ) ;
										chars[i]->resetTimer ( ) ;
										
									}
									
								}
								
							} // Collision avec les points
							
							// On regarde si le personnage est Super Pacman et si son timer a expiré
							// ~ normalement terminé - à tester
							if ( chars[i]->getStatus ( ) == Character::SUPER_PACMAN && chars[i]->getTimer ( ) > 10.f )
							{
								
								chars[i]->setStatus ( Character::PACMAN ) ;
								
							}
							
						} // Personnage i existant
						
					} // Parcourt de la liste des personnages
					
					// Fais spawn Pacman au bout de 30 secondes
					if ( ! pacman_spawn && now > 30.f )
					{
						
						bool trouve = false ;
						
						while ( ! trouve )
						{
							
							unsigned char pacman_id = static_cast < unsigned char > ( rand ( ) ) % party_data->party->getSlot ( ) ;
							
							if ( chars[pacman_id] != NULL )
							{
								
								chars[pacman_id]->setStatus ( Character::PACMAN ) ;
								trouve = true ;
								
							}
							
						}
						
					}
					
				}
				
			} // Partie en cours
			// Partie en attente
			else if ( party_data->party->getStatus ( ) == Party::WAITING )
			{
				
				if ( ! scoring )
				{
					
					unsigned char nb_players = 0 ;
					Character** chars = party_data->party->getChars ( ) ;
					
					for ( unsigned char i = 0 ; i < party_data->party->getSlot ( ) ; i ++ )
					{
						
						if ( chars[i] != NULL )
						{
							
							nb_players ++ ;
							
						}
						
					}
					
					// Si tous les joueurs sont rendus
					if ( nb_players == party_data->party->getSlot ( ) || clk.GetElapsedTime ( ) > 30.f )
					{
						
						party_data->party->setStatus ( Party::PLAYING ) ;
						clk.Reset ( ) ;
						now = 0.f ;
						
					}
					
				}
				else
				{
					
					if ( now > 10.f )
						party_data->party->setStatus ( Party::ENDED ) ;
					
				}
				
			} // Partie en attente
			
			// Débloque l'accès à la partie
			last_update = now ;
			party_data->p_mutex->Unlock ( ) ;
			
		} // update car plus de 50 ms de retard
		
		// On patiente 20 ms
		Sleep ( 0.020f ) ;
		
	} // Boucle mise à jour de la partie
	
	// Libération de la mémoire
	delete ( *party_data->thread ) ;
	( *party_data->thread ) = NULL ;
	
}

int main ( int argc, char *argv[] )
{
	
	unsigned char slot ;
	std::string map_path ;
	
	srand ( time ( NULL ) ) ;
	
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
	(*p_thread)->Launch ( ) ;
	
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
		
		if ( threads[i] != NULL )
			threads[i]->Wait ( ) ;
			
		delete threads[i] ;
		delete clients[i] ;
		
	}
	
	delete[] threads ;
	delete[] clients ;
	delete new_client ;
	if ( *p_thread != NULL )
		delete (*p_thread) ;
	delete p_thread ;
	
	return EXIT_SUCCESS ;
	
}
