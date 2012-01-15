#include <cstdlib>
#include <iostream>
#include "action.h"
#include <SFML/System.hpp>
#include "Party.h"
#include <sstream>
#include "network.h"

std::string int2str ( int i )
{
	
	std::ostringstream out ;
	out << i ;
	return out.str ( ) ;
	
}

using namespace sf ;

struct NetworkData
{
	bool* quit ;
	SocketTCP* sck ;
	Party* party ;
	Mutex* p_mutex ;
	const Input* ipt ;
	myOption* opt ;
} ;

void manage_network ( void* data )
{
	
	NetworkData* net_data = static_cast < NetworkData* > ( data ) ;
	bool quitter = false ;
	
	while ( ! quitter )
	{
		
		net_data->p_mutex->Lock ( ) ;
		if ( net_data->opt->getDebug ( ) ) std::cout << "Mutex obtenu par le réseau" << std::endl ;
		
		// Réception des données
		Packet pck_to_receive ;
		net_data->sck->Receive ( pck_to_receive ) ;
		
		std::string client_cmd ;
		pck_to_receive >> client_cmd ;
		
		if ( client_cmd == "Data" )
		{
			
			if ( net_data->opt->getDebug ( ) ) std::cout << "Données de type Data reçus du serveur" << std::endl ;
			pck_to_receive >> *(net_data->party) ;
			if ( net_data->opt->getDebug ( ) ) std::cout << "Données de type Data bien analysées" << std::endl ;
			
		}
		
		// Envoie de données
		Packet pck_to_send ;
		
		if ( *(net_data->quit) == true )
		{
			
			pck_to_send << std::string ( "Quit" ) ;
			quitter = true ;
			
		}
		else
		{
			
			pck_to_send << std::string ( "Movement" ) ;
			
			unsigned char mvt1 = Character::NONE, mvt2 = Character::NONE ;
			
			if ( net_data->ipt->IsKeyDown ( net_data->opt->getUpKey ( ) ) )
				mvt1 = Character::NORTH ;
			
			if ( mvt1 == Character::NONE && net_data->ipt->IsKeyDown ( net_data->opt->getDownKey ( ) ) )
				mvt1 = Character::SOUTH ;
			else if ( net_data->ipt->IsKeyDown ( net_data->opt->getDownKey ( ) ) )
				mvt2 = Character::SOUTH ;
			
			if ( mvt1 == Character::NONE && net_data->ipt->IsKeyDown ( net_data->opt->getLeftKey ( ) ) )
				mvt1 = Character::WEST ;
			else if ( mvt2 == Character::NONE && net_data->ipt->IsKeyDown ( net_data->opt->getLeftKey ( ) ) )
				mvt2 = Character::WEST ;
			
			if ( mvt1 == Character::NONE && net_data->ipt->IsKeyDown ( net_data->opt->getRightKey ( ) ) )
				mvt1 = Character::EAST ;
			else if ( mvt2 == Character::NONE && net_data->ipt->IsKeyDown ( net_data->opt->getRightKey ( ) ) )
				mvt2 = Character::EAST ;
			
			pck_to_send << mvt1 << mvt2 ;
			
		}
		
		net_data->sck->Send ( pck_to_send ) ;
		
		if ( net_data->party->getStatus ( ) == Party::ENDED )
			*(net_data->quit) = true ;
		
		net_data->p_mutex->Unlock ( ) ;
		
		Sleep ( 0.050f ) ;
		
	}
	
	// Déconnexion du client
	net_data->sck->Close ( ) ;
	
}

int play ( sf::RenderWindow& window, myOption& opt, sf::SocketTCP& sck )
{
	
	if ( ! sck.IsValid ( ) )
	{
		
		if ( opt.getDebug ( ) ) std::cout << "Socket envoyer à play invalide" << std::endl ;
		exit ( EXIT_FAILURE ) ;
		
	}
	
	bool quitter = false ;
	int action = 1 ;
	
	Party p ;
	Mutex p_mutex ;
	NetworkData net_data ;
	net_data.quit = & quitter ;
	net_data.sck = & sck ;
	net_data.party = & p ;
	net_data.p_mutex = & p_mutex ;
	net_data.ipt = &window.GetInput ( ) ;
	net_data.opt = &opt ;
	Thread t ( manage_network, static_cast < void* > ( & net_data ) ) ;
	t.Launch ( ) ;
	
	Clock clk ;
	
	if ( opt.getDebug ( ) ) std::cout << "Chargement des images" << std::endl ;
	
    // Chargement des sprites de fantomes
    Image ghost_image[5][2] ;
	Sprite ghost_sprite[5][2] ;
	std::string ghost_colors[] = { "blue", "orange", "red", "yellow", "" } ;
	
	for ( int i = 0 ; i < 5 ; i ++ )
	{
		
		std::string path = std::string ( "pics/ghost1" ) + ghost_colors[i] + ".png" ;
		if ( ! ghost_image[i][0].LoadFromFile ( path ) ) // Si le chargement du fichier a échoué
		{
			
			if ( opt.getDebug ( ) ) std::cout << "Image manquante" << std::endl ;
			exit ( EXIT_FAILURE ) ;
		
		}
		else // Si le chargement de l'image a réussi
		{
			ghost_sprite[i][0].SetImage ( ghost_image[i][0] ) ;
		}
		
		path = std::string ( "pics/ghost2" ) + ghost_colors[i] + ".png" ;
		if ( ! ghost_image[i][1].LoadFromFile ( path ) ) // Si le chargement du fichier a échoué
		{
			
			if ( opt.getDebug ( ) ) std::cout << "Image manquante" << std::endl ;
			exit ( EXIT_FAILURE ) ;
		
		}
		else // Si le chargement de l'image a réussi
		{
			ghost_sprite[i][1].SetImage ( ghost_image[i][1] ) ;
		}
		
	}
	
	// Chargement des sprites de Pacman
	Image pacman_image[2] ;
	Sprite pacman_sprite[2] ;
	
	if ( ! pacman_image[0].LoadFromFile ( "pics/Pac1.png" ) || ! pacman_image[1].LoadFromFile ( "pics/Pac2.png" ) ) // Si le chargement du fichier a échoué
	{
		
		if ( opt.getDebug ( ) ) std::cout << "Image manquante" << std::endl ;
		exit ( EXIT_FAILURE ) ;
	
	}
	else // Si le chargement de l'image a réussi
	{
		pacman_sprite[0].SetImage ( pacman_image[0] ) ;
		pacman_sprite[1].SetImage ( pacman_image[1] ) ;
	}
	
	// Chargement des sprites de Super Pacman
	
	Image super_pacman_image[2] ;
	Sprite super_pacman_sprite[2] ;
	
	if ( ! super_pacman_image[0].LoadFromFile ( "pics/Pac1.png" ) || ! super_pacman_image[1].LoadFromFile ( "pics/Pac2.png" ) ) // Si le chargement du fichier a échoué
	{
		
		if ( opt.getDebug ( ) ) std::cout << "Image manquante" << std::endl ;
		exit ( EXIT_FAILURE ) ;
	
	}
	else // Si le chargement de l'image a réussi
	{
		super_pacman_sprite[0].SetImage ( super_pacman_image[0] ) ;
		super_pacman_sprite[1].SetImage ( super_pacman_image[1] ) ;
	}
	
	// Chargement des sprite de mur
	Image wall_image[16] ;
	Sprite wall_sprite[16] ;
	
	for ( int i = 0 ; i < 16 ; i ++ )
	{
		
		std::string path = std::string ( "pics/wall" ) + int2str ( i + 1 ) + ".png" ;
		if ( ! wall_image[i].LoadFromFile ( path ) ) // Si le chargement du fichier a échoué
		{
			
			if ( opt.getDebug ( ) ) std::cout << "Image manquante" << std::endl ;
			exit ( EXIT_FAILURE ) ;
		
		}
		else // Si le chargement de l'image a réussi
		{
			wall_sprite[i].SetImage ( wall_image[i] ) ;
		}
		
	}
	
	if ( opt.getDebug ( ) ) std::cout << "Chargement des images terminé" << std::endl ;
	
	// Fin du chargement des sprites
	
    while ( ! quitter ) // Boucle d'affichage
    {
		
		p_mutex.Lock ( ) ;
		if ( opt.getDebug ( ) ) std::cout << "Mutex obtenu par l'afficheur" << std::endl ;
		
		window.Clear ( ) ;
		
		if ( p.getStatus ( ) == Party::WAITING )
		{
			
			if ( opt.getDebug ( ) ) std::cout << "Partie en attente" << std::endl ;
			
			String msg = String ( p.getMessage ( ) ) ;
			
			msg.SetColor ( Color ( 255, 255, 255, 255 ) ) ;
			msg.SetX ( 250 ) ;
			msg.SetY ( ( window.GetHeight ( ) + 30 ) / 2 ) ;
			
			window.Draw ( msg ) ;
			
		}
		else
		{
			
			unsigned int
				w = p.getWidth ( ),
				h = p.getHeight ( ) ;
			unsigned char
				c ;
			float
				c_size = window.GetHeight ( ) / h,
				x_decalage = window.GetWidth ( ) - c_size * static_cast < float > ( w ) ;
			Shape
				s ;
			Character**
				chars = p.getChars ( ) ;
			
			// Dessin de la carte
			for ( unsigned int i = 0 ; i < w ; i ++ )
			{
				
				for ( unsigned int j = 0 ; j < h ; j ++ )
				{
					
					c = p.getCase ( i, j ) ;
					
					if ( c == Party::PAC_POINT )
					{
						
						s = Shape::Rectangle (
							x_decalage + c_size * ( static_cast < float > ( i ) + 0.375f ),
							c_size * ( static_cast < float > ( j ) + 0.375f ),
							x_decalage + c_size * ( static_cast < float > ( i ) + 0.625f ),
							c_size * ( static_cast < float > ( j ) + 0.625f ),
							Color::White ) ;
						window.Draw ( s ) ;
						
					}
					else if ( c == Party::SUPERPAC_POINT )
					{
						
						s = Shape::Rectangle (
							x_decalage + c_size * ( static_cast < float > ( i ) + 0.25f ),
							c_size * ( static_cast < float > ( j ) + 0.25f ),
							x_decalage + c_size * ( static_cast < float > ( i ) + 0.75f ),
							c_size * ( static_cast < float > ( j ) + 0.75f ),
							Color::White ) ;
						window.Draw ( s ) ;
						
					}
					else if ( c == Party::WALL )
					{
						
						wall_sprite[6].Resize ( c_size, c_size ) ;
						wall_sprite[6].SetPosition (
							x_decalage + c_size * static_cast < float > ( i ),
							c_size * static_cast < float > ( j ) ) ;
						
						window.Draw ( wall_sprite[6] ) ;
						
					}
					
				}
				
			} // Dessin de la carte
			
			// Cherche s'il y a un Super Pacman
			bool has_super_pacman = false ;
			for ( unsigned char i = 0 ; i < p.getSlot ( ) ; i ++ )
			{
				
				if ( chars[i] != NULL )
					if ( chars[i]->getStatus ( ) == Character::SUPER_PACMAN )
					{
						
						has_super_pacman = true ;
						break ;
						
					}
				
			}
			
			String msg = String ( "Timer :" ) ;
			msg.SetColor ( Color ( 255, 255, 255, 255 ) ) ;
			
			msg.SetX ( 50 ) ;
			msg.SetY ( 50 ) ;
			
			window.Draw ( msg ) ;
			
			msg.SetText ( int2str ( static_cast < int > ( p.getTimer ( ) ) ) ) ;
			
			msg.SetX ( 75 ) ;
			msg.SetY ( 85 ) ;
			
			window.Draw ( msg ) ;
			
			// Affiche les personnages dans les infos et sur la carte
			for ( unsigned char i = 0 ; i < p.getSlot ( ) ; i ++ )
			{
				
				if ( chars[i] == NULL )
				{
					
					msg.SetText ( "Slot libre" ) ;
					
					msg.SetX ( 100 ) ;
					msg.SetY ( 100 * i + 200 ) ;
					
					window.Draw ( msg ) ;
					
				}
				else
				{
					
					msg.SetText ( chars[i]->getName ( ) ) ;
					
					msg.SetX ( 100 ) ;
					msg.SetY ( 100 * i + 200 ) ;
					
					window.Draw ( msg ) ;
					
					msg.SetText ( "Points : " + int2str ( chars[i]->getPoint ( ) ) ) ;
					msg.SetX ( 100 ) ;
					msg.SetY ( 100 * i + 230 ) ;
					
					window.Draw ( msg ) ;
					
					unsigned char t = static_cast < unsigned char > ( clk.GetElapsedTime ( ) ) % 2 ;
					Sprite* spt ;
					
					if ( chars[i]->getStatus ( ) == Character::SUPER_PACMAN )
						spt = & ( super_pacman_sprite[t] ) ;
					else if ( chars[i]->getStatus ( ) == Character::PACMAN )
						spt = & ( pacman_sprite[t] ) ;
					else if ( chars[i]->getStatus ( ) == Character::GHOST && has_super_pacman )
						spt = & ( ghost_sprite[4][t] ) ;
					else
						spt = & ( ghost_sprite[i][t] ) ;
					
					// Dessin dans les infos
					spt->Resize ( 50, 50 ) ;
					spt->SetPosition ( 25, 100 * i + 200 ) ;
					
					window.Draw ( *spt ) ;
					
					// Dessin sur la carte
					spt->Resize ( c_size, c_size ) ;
					spt->SetPosition (
						x_decalage + c_size * chars[i]->getX ( ),
						c_size * chars[i]->getX ( ) ) ;
					
					window.Draw ( *spt ) ;
					
				}
				
			}
			
		}
		
		p_mutex.Unlock ( ) ;
		
		window.Display ( ) ;
		
        Event event ;
        while ( window.GetEvent ( event ) ) // Boucle des évènements
        {
			
			switch ( event.Type ) // Type de l'évènement en attente :
			{
				
			case Event::Closed : // Croix en haut à droite
				action = 0 ;
				quitter = true ;
			break;
			
			case Event::KeyPressed : // Appui sur une touche du clavier
				if ( event.Key.Code == opt.getCancelKey() ) // Appui sur la touche Haut
				{
					action = 1 ;
					quitter = true ;
				}
			break;
			
			default :
			break;
			
			} // Switch des évènements
			
		} // Boucle des évènements
		
		Sleep ( 0.050f ) ;
		
	} // Boucle d'affichage
	
	t.Wait ( ) ;
	
	return action;
	
}
