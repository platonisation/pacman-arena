#include <cstdlib>
#include <iostream>
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
		s_droit = String ( "Droite" ),
		s_quitter = String ( "Quitter" ),
		//touches modifiables
		s_gaucheM = String ( ),
		s_hautM = String ( ),
		s_basM = String ( ),
		s_droitM = String ( ) ;
		
	std::string
		gauche = std::string ( ),
		haut = std::string ( ),
		bas = std::string ( ) ,
		droit = std::string ( ) ;
		
	gauche = static_cast<char>( opt.getLeftKey ( ) );
	haut = static_cast<char>( opt.getUpKey ( ) );
	bas = static_cast<char>( opt.getDownKey ( ) );
	droit = static_cast<char>( opt.getRightKey ( ) );
	std::cout<<static_cast<char>( opt.getLeftKey ( ) );
		
	s_gaucheM.SetText( gauche ) ;
	s_droitM.SetText( droit ) ;
	s_hautM.SetText( haut ) ;
	s_basM.SetText( bas ) ;
	
	s_touches.SetPosition ( 70, window.GetHeight ( ) - 300 ) ;
	s_haut.SetPosition ( 70, window.GetHeight ( ) - 240 ) ;
	s_gauche.SetPosition ( 70, window.GetHeight ( ) - 200 ) ;
	s_bas.SetPosition ( 70, window.GetHeight ( ) - 160 ) ;
	s_droit.SetPosition ( 70, window.GetHeight ( ) - 120 ) ;
	s_quitter.SetPosition ( 70, window.GetHeight ( ) - 50 ) ;
	//touches modifiables
	s_hautM.SetPosition ( 250, window.GetHeight ( ) - 240 ) ;
	s_gaucheM.SetPosition ( 250, window.GetHeight ( ) - 200 ) ;
	s_basM.SetPosition ( 250, window.GetHeight ( ) - 160 ) ;
	s_droitM.SetPosition ( 250, window.GetHeight ( ) - 120 ) ;
	
	Shape Rect = Shape::Rectangle(65,(window.GetHeight()-75) , (window.GetWidth()+23)/2,(window.GetHeight()+100)/2 , Color(0,0,0,0), 5.f, Color::White);

	
    while ( ! quitter ) // Boucle d'affichage
    {
		
		window.Clear ( ) ;
		
		s_touches.SetColor ( Color ( 255, 255, 255, 150 ) ) ;
		s_haut.SetColor ( Color ( 255, 255, 255, ( action == 3 ) ? 255 : 150 ) ) ;
		s_gauche.SetColor ( Color ( 255, 255, 255, ( action == 2 ) ? 255 : 150 ) ) ;
		s_bas.SetColor ( Color ( 255, 255, 255, ( action == 0 ) ? 255 : 150 ) ) ;
		s_droit.SetColor ( Color ( 255, 255, 255, ( action == 5 ) ? 255 : 150 ) ) ;
		s_quitter.SetColor ( Color ( 255, 255, 255, ( action == 4 ) ? 255 : 150 ) ) ;
		//Touches modifiables
		s_hautM.SetColor ( Color ( 255, 255, 255, ( action == 3 ) ? 255 : 150 ) ) ;
		s_gaucheM.SetColor ( Color ( 255, 255, 255, ( action == 2 ) ? 255 : 150 ) ) ;
		s_basM.SetColor ( Color ( 255, 255, 255, ( action == 0 ) ? 255 : 150 ) ) ;
		s_droitM.SetColor ( Color ( 255, 255, 255, ( action == 5 ) ? 255 : 150 ) ) ;
		
		window.Draw ( s_touches ) ;
		window.Draw ( s_haut ) ;
		window.Draw ( s_gauche ) ;
		window.Draw ( s_bas ) ;
		window.Draw ( s_droit ) ;
		window.Draw ( s_hautM ) ;
		window.Draw ( s_gaucheM ) ;
		window.Draw ( s_basM ) ;
		window.Draw ( s_droitM	 ) ;
		window.Draw ( s_quitter ) ;
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
					else if ( action == 5 )
						action = 0 ;
					else
						action ++ ;
				}
				else if ( event.Key.Code == opt.getDownKey() ) // Appui sur la touche Bas
				{
					if ( action == 0 )
						action = 5 ;
					else if ( action == 2 )
						action = 0 ;
					else
						action -- ;
				}
				else if ( event.Key.Code == opt.getValidKey() ) // Appui sur la touche Valider
				{
					if ( action == 4 )
					{
						quitter = true ;
						action = 1 ;
					}
					else
					{
						working = !working;
						Event event2;
						//boucle de choix de touche
						while ( working )
						{
							while ( window.GetEvent( event2 ) )
							{
								if ( event2.Type == Event::KeyPressed )
								{
									if ( action == 5 )
									{
										opt.setRightKey( event2.Key.Code ) ;
										droit = static_cast<char>( event2.Key.Code );
										s_droitM.SetText( droit ) ;
									}
									else if ( action == 2 )
									{
										opt.setLeftKey( event2.Key.Code ) ;
										gauche = static_cast<char>(event2.Key.Code);
										s_gaucheM.SetText( gauche ) ;
									}
									else if ( action == 3 )
									{
										opt.setUpKey( event2.Key.Code ) ;
										haut = static_cast<char>( event2.Key.Code );
										s_hautM.SetText( haut ) ;
									}
									else if ( action == 0 )
									{
										opt.setDownKey ( event2.Key.Code ) ;
										bas = static_cast<char>( event2.Key.Code );
										s_basM.SetText( bas ) ;
									}
									
									working = !working ;
									
								} // fin condition key pressed
								
							} // fin detection evenement
							
						} // fin boucle d'attente d'une touche pressé
						
					} // fin condition modification touche
					
				} // fin appuie touche return
				
			break;
			
			default :
			break;
			
			} // Switch des évènements
			
		} // Boucle des évènements
		
	} // Boucle d'affichage
	
	return action;
	
}
