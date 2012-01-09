#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "action.h"

using namespace sf;

int create ( sf::RenderWindow& window, myOption& opt, sf::SocketTCP& sck ) 
{
	
    bool quitter = false ;
    int action = 4 ;
	
	String
		s_players = String ( "Nombres joueurs :" ),
		s_map = String ( "Carte :" ),
		s_valid = String ( "Valider" ),
		s_back = String ( "Retour" ) ;
	
	s_players.SetPosition ( 70, window.GetHeight ( ) - 240 ) ;
	s_map.SetPosition ( 70, window.GetHeight ( ) - 200 ) ;
	s_valid.SetPosition ( 70, window.GetHeight ( ) - 140 ) ;
	s_back.SetPosition ( 70, window.GetHeight ( ) - 100 ) ;
	
    while ( ! quitter ) // Boucle d'affichage
    {
		
		window.Clear ( ) ;
		
		s_players.SetColor ( Color ( 255, 255, 255, ( action == 4 ) ? 255 : 150 ) ) ;
		s_map.SetColor ( Color ( 255, 255, 255, ( action == 3 ) ? 255 : 150 ) ) ;
		s_valid.SetColor ( Color ( 255, 255, 255, ( action == 2 ) ? 255 : 150 ) ) ;
		s_back.SetColor ( Color ( 255, 255, 255, ( action == 0 ) ? 255 : 150 ) ) ;
		
		s_valid.SetX ( ( action == 2 ) ? 90 : 70 ) ;
		s_back.SetX ( ( action == 0 ) ? 90 : 70 ) ;
		
		window.Draw ( s_players ) ;
		window.Draw ( s_map ) ;
		window.Draw ( s_valid ) ;
		window.Draw ( s_back ) ;
		
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
		
	} // Boucle d'affichage
	
	return action;
	
}
