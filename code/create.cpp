#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "action.h"
#include <iostream>
#include <string>

#include <dirent.h> // struct dirent, opendir(), readdir(), closedir()
#include <sys/types.h> // DIR type 

using namespace sf;

int create ( sf::RenderWindow& window, myOption& opt, sf::SocketTCP& sck ) 
{
/*	//lecture d'un repertoire
	DIR * dir;
	struct dirent * entry;
	dir = opendir("maps/" );
	std::string test;

	while((entry = readdir(dir)) != NULL)
		test << entry->d_name;
	closedir(dir);*/
	
	/*# DIR * dir;
# struct dirent * entry;
#
# dir = opendir("/usr/bin" );
# if( dir == NULL )
#   perror("" );
# while((entry = readdir(dir)) != NULL)
#   fprintf(stdout, "Inside /usr/bin is something called %s\n", entry->d_name);
# fprintf(stdout, "\n" );
# closedir(dir);
*/
	
	
    bool quitter = false ;
    int action = 1 ;
    unsigned char focus = 1 ;
    
    char nbPlayers = 51 ; //code ascii de 3
    std::string listMap;
	
	String
		s_players = String ( "Joueurs :" ),
		s_map = String ( "Carte :" ),
		s_valid = String ( "Valider" ),
		s_back = String ( "Retour" ) ,
		s_choseMap = String ( "Ma map" ),
		s_nbPlayers = String ( "3" );
	
	s_players.SetPosition ( 70, window.GetHeight ( ) - 240 ) ;
	s_map.SetPosition ( 70, window.GetHeight ( ) - 200 ) ;
	s_valid.SetPosition ( 70, window.GetHeight ( ) - 140 ) ;
	s_back.SetPosition ( 70, window.GetHeight ( ) - 100 ) ;
	s_choseMap.SetPosition ( 200, window.GetHeight ( ) -200 ) ;
	s_nbPlayers.SetPosition ( 200, window.GetHeight ( ) - 240 ) ;
	
    while ( ! quitter ) // Boucle d'affichage
    {
		
		window.Clear ( ) ;
		
		s_players.SetColor ( Color ( 255, 255, 255, ( focus == 1 ) ? 255 : 150 ) ) ;
		s_map.SetColor ( Color ( 255, 255, 255, ( focus == 2 ) ? 255 : 150 ) ) ;
		s_valid.SetColor ( Color ( 255, 255, 255, ( focus == 3 ) ? 255 : 150 ) ) ;
		s_back.SetColor ( Color ( 255, 255, 255, ( focus == 4 ) ? 255 : 150 ) ) ;
		s_choseMap.SetColor( Color ( 255, 255, 255, 150 ) ) ;
		s_nbPlayers.SetColor ( Color ( 255, 255, 255, 255 ) ) ;
		
		s_valid.SetX ( ( focus == 3 ) ? 90 : 70 ) ;
		s_back.SetX ( ( focus == 4 ) ? 90 : 70 ) ;
		
		window.Draw ( s_players ) ;
		window.Draw ( s_map ) ;
		window.Draw ( s_valid ) ;
		window.Draw ( s_back ) ;
		window.Draw ( s_choseMap ) ;
		window.Draw( s_nbPlayers ) ;
		
		window.Display ( ) ;
		
        Event event ;
        while ( window.GetEvent ( event ) ) // Boucle des évènements
        {
			
			switch ( event.Type ) // Type de l'évènement en attente :
			{
				
			case Event::Closed : // Croix en haut à droite
				action = 0;
				quitter = true;
			break;
			
			case Event::KeyPressed : // Appui sur une touche du clavier
				if ( event.Key.Code == opt.getUpKey() ) // Appui sur la touche Haut
				{
					if ( focus == 1 )
						focus = 4 ;
					else
						focus -- ;

				}
				else if ( event.Key.Code == opt.getDownKey() ) // Appui sur la touche Bas
				{
					if ( focus == 4 )
						focus = 1 ;
					else
						focus ++ ;
				}
				else if ( event.Key.Code == opt.getLeftKey() ) // Appui sur la touche Gauche
				{
					if ( focus == 1 )
					{
						if( nbPlayers > 50 )
							nbPlayers -- ;
						std::string tmp;
						tmp += nbPlayers; 
						
						s_nbPlayers.SetText( tmp ) ;
					}
					else if ( focus == 2 )
					{
						action = 0 ;
						//gestion de tous les fichiers maps
					}
					else
						action ++ ;
				}
				else if ( event.Key.Code == opt.getRightKey() ) // Appui sur la touche Bas
				{
					if ( focus == 1 )
					{
						if( nbPlayers < 52 )
							nbPlayers ++ ;
						std::string tmp;
						tmp += nbPlayers; 
						
						s_nbPlayers.SetText( tmp ) ;
					}
					else if ( focus == 2 )
					{
						action = 0 ;
						//gestion de tous les fichiers maps
					}
					else
						action -- ;
				}
				else if ( event.Key.Code == opt.getValidKey() ) // Appui sur la touche Valider
				{
					quitter = true ;
					if ( focus == 4 )
						action = 1 ;
					else
					{
						action = 5 ;
						// connection
					}
				}
			break;
			
			default :
			break;
			
			} // Switch des évènements
			
		} // Boucle des évènements
		
	} // Boucle d'affichage
	
	return action;
	
}
