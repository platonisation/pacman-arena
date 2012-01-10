#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "action.h"

using namespace sf;

int option ( RenderWindow& window, myOption& opt )
{
	
    bool quitter = false ;
    bool working = false;
    int action = 4 ;
	
	String
		s_touches = String ( "Touches" ),
		s_gauche = String ( "Gauche" ),
		s_haut = String ( "Haut" ),
		s_bas = String ( "Bas" ) ,
		s_droit = String ( "Droite" ) ;
	
	s_touches.SetPosition ( 70, window.GetHeight ( ) - 300 ) ;
	s_haut.SetPosition ( 70, window.GetHeight ( ) - 240 ) ;
	s_gauche.SetPosition ( 70, window.GetHeight ( ) - 200 ) ;
	s_bas.SetPosition ( 70, window.GetHeight ( ) - 160 ) ;
	s_droit.SetPosition ( 70, window.GetHeight ( ) - 120 ) ;
	Shape Rect = Shape::Rectangle(65,(window.GetHeight()-75) , (window.GetWidth()+23)/2,(window.GetHeight()+100)/2 , Color(0,0,0,0), 5.f, Color::White);

	
    while ( ! quitter ) // Boucle d'affichage
    {
		
		window.Clear ( ) ;
		
		s_touches.SetColor ( Color ( 255, 255, 255, 150 ) ) ;
		s_haut.SetColor ( Color ( 255, 255, 255, ( action == 3 ) ? 255 : 150 ) ) ;
		s_gauche.SetColor ( Color ( 255, 255, 255, ( action == 2 ) ? 255 : 150 ) ) ;
		s_bas.SetColor ( Color ( 255, 255, 255, ( action == 0 ) ? 255 : 150 ) ) ;
		s_droit.SetColor ( Color ( 255, 255, 255, ( action == 4 ) ? 255 : 150 ) ) ;
		
		window.Draw ( s_touches ) ;
		window.Draw ( s_haut ) ;
		window.Draw ( s_gauche ) ;
		window.Draw ( s_bas ) ;
		window.Draw ( s_droit ) ;
		window.Draw ( Rect ) ;
		
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
				{
					//boucle de choix de touche
					working = !working ;
					if(working)
					{
						switch(action)
						{
							case 0 :
								opt.setRightKey( event.Key.Code ) ;
							break ;
							
							case 2 :
								opt.setLeftKey( event.Key.Code ) ;
							break ;
							
							case 3 :
								opt.setUpKey( event.Key.Code ) ;
							break ;
							
							case 4 :
								opt.setDownKey ( event.Key.Code ) ;
							break ;
							default :
							break;
						}
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
