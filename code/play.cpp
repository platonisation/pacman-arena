#include <cstdlib>
#include <iostream>
#include "action.h"
#include <SFML/System.hpp>
#include "Party.h"
#include <sstream>

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
} ;

void manage_network ( void* data )
{
	
	NetworkData* net_data = static_cast < NetworkData* > ( data ) ;
	
	
	
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
	Thread t ( manage_network, static_cast < void* > ( & net_data ) ) ;
	t.Launch ( ) ;
	
	Clock clk ;
	
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
	
	// Fin du chargement des sprites
	
    while ( ! quitter ) // Boucle d'affichage
    {
		
		p_mutex.Lock ( ) ;
		
		window.Clear ( ) ;
		
		if ( p.getStatus ( ) == Party::WAITING )
		{
			
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
			
			// Affiche les personnages dans les infos et sur la carte
			for ( unsigned char i = 0 ; i < p.getSlot ( ) ; i ++ )
			{
				
				if ( chars[i] == NULL )
				{
					
					String msg = String ( "Slot libre" ) ;
					
					msg.SetColor ( Color ( 255, 255, 255, 255 ) ) ;
					msg.SetX ( 100 ) ;
					msg.SetY ( 100 * static_cast < int > ( i + 1 ) ) ;
					
					window.Draw ( msg ) ;
					
				}
				else
				{
					
					String msg = String ( chars[i]->getName ( ) ) ;
					
					msg.SetColor ( Color ( 255, 255, 255, 255 ) ) ;
					msg.SetX ( 100 ) ;
					msg.SetY ( ( window.GetHeight ( ) + 30 ) / 2 ) ;
					
					window.Draw ( msg ) ;
					
					msg.SetText ( "Points : " + int2str ( chars[i]->getPoint ( ) ) ) ;
					msg.SetX ( 150 ) ;
					msg.SetY ( ( window.GetHeight ( ) + 30 ) / 2 + 40 ) ;
					
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
					spt->SetPosition ( 25, ( window.GetHeight ( ) + 30 ) / 2 ) ;
					
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
				if ( event.Key.Code == opt.getUpKey() ) // Appui sur la touche Haut
				{
					if ( action == 0 )
						action = 2 ;
					else if ( action == 4 )
						action = 0 ;
					else
						action ++ ;
				}
				else if ( event.Key.Code == opt.getDownKey() ) // Appui sur la touche Bas
				{
					if ( action == 0 )
						action = 4 ;
					else if ( action == 2 )
						action = 0 ;
					else
						action -- ;
				}
				else if ( event.Key.Code == opt.getValidKey() ) // Appui sur la touche Valider
					quitter = true ;
			break;
			
			default :
			break;
			
			} // Switch des évènements
			
		} // Boucle des évènements
		
		p_mutex.Unlock ( ) ;
		
		Sleep ( 0.050f ) ;
		
	} // Boucle d'affichage
	
	t.Wait ( ) ;
	
	return action;
	
}
