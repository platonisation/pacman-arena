#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "action.h"

using namespace sf;

int menu ( RenderWindow& window, myOption& opt )
{
	
    bool quitter = false ;
    int action = 4 ;
	
	String
		s_join = String ( "Rejoindre une partie" ),
		s_create = String ( "Créer une partie" ),
		s_option = String ( "Parametres" ),
		s_quit = String ( "Quitter" ) ;
	
	s_join.SetPosition ( 70, window.GetHeight ( ) - 240 ) ;
	s_create.SetPosition ( 70, window.GetHeight ( ) - 200 ) ;
	s_option.SetPosition ( 70, window.GetHeight ( ) - 140 ) ;
	s_quit.SetPosition ( 70, window.GetHeight ( ) - 100 ) ;
	
    while ( ! quitter ) // Boucle d'affichage
    {
		
		window.Clear ( ) ;
		
		s_join.SetColor ( Color ( 255, 255, 255, ( action == 4 ) ? 255 : 150 ) ) ;
		s_create.SetColor ( Color ( 255, 255, 255, ( action == 3 ) ? 255 : 150 ) ) ;
		s_option.SetColor ( Color ( 255, 255, 255, ( action == 2 ) ? 255 : 150 ) ) ;
		s_quit.SetColor ( Color ( 255, 255, 255, ( action == 0 ) ? 255 : 150 ) ) ;
		
		s_join.SetX ( ( action == 4 ) ? 90 : 70 ) ;
		s_create.SetX ( ( action == 3 ) ? 90 : 70 ) ;
		s_option.SetX ( ( action == 2 ) ? 90 : 70 ) ;
		s_quit.SetX ( ( action == 0 ) ? 90 : 70 ) ;
		
		window.Draw ( s_join ) ;
		window.Draw ( s_create ) ;
		window.Draw ( s_option ) ;
		window.Draw ( s_quit ) ;
		
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
