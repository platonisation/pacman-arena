#include <cstdlib>
#include <iostream>
#include <SFML/System.hpp>
#include <string>

#include "action.h"

using namespace sf;

int join ( RenderWindow& window, myOption& opt, SocketTCP& sck ) 
{

	Shape Rect = Shape::Rectangle((window.GetWidth()-230)/2,(window.GetHeight()-40)/2 , (window.GetWidth()+230)/2,(window.GetHeight()+40)/2 , Color(0,0,0,0), 5.f, Color::White);
	
	int action = 1;
	bool quitter = false;
	std::string ip;
	String ipDraw;
	ipDraw.SetColor(Color::White);
	ipDraw.SetPosition ( (window.GetWidth()-228)/2, (window.GetHeight()-35)/2 );
	
	while( !quitter )
	{
		window.Clear ( ) ;
		window.Draw(ipDraw);
		window.Draw(Rect);
		window.Display ( ) ;
		 Event event ;
		 while ( window.GetEvent ( event ) ) // Boucle des évènements
			{
				
				switch ( event.Type ) // Type de l'évènement en attente :
				{
					case Event::Closed : // Croix en haut à droite
						quitter = true;
						action = 0;
					break;
					case Event::KeyPressed : // Appui sur une touche du clavier
					{
						if((event.Key.Code <= Key::Num9 && event.Key.Code >= Key::Num0)) // Si on tape un chiffre en 0 et 9
						{
							ip += static_cast<char>(event.Key.Code);
							ipDraw.SetText(ip);
							window.Draw(ipDraw);
						}
						if((event.Key.Code <= Key::Numpad9 && event.Key.Code >= Key::Numpad0)) // Si on tape un chiffre en 0 et 9
						{
							ip += static_cast<char>(event.Key.Code+Key::Num0-Key::Numpad0);
							ipDraw.SetText(ip);
							window.Draw(ipDraw);
						}
						switch(event.Key.Code)
						{
							case Key::Period:  // touche .
								ip += '.';
								ipDraw.SetText(ip);
							break;
							case Key::Back:   
								if(ip.size() == 0)
								{
									action = 1;
									quitter = true;
								}
								else
								{
									ip.resize(ip.length()-1);// supprime le dernier charactere
									ipDraw.SetText(ip);
									
								}
							break;
							case Key::Return:   // touche entrées
								if (sck.Connect(8910, ip) == Socket::Done)
								{
									
									Sleep ( 0.050f ) ;
									
									char* c = new char[2] ;
									std::size_t r ;
									
									sck.Receive ( c, static_cast < std::size_t > ( sizeof ( char ) * 2 ), r ) ;
									
									if ( c[0] == '0' )
									{
										quitter = true;
										action = 1 ;
									}
									else
									{
										quitter = true;
										action = 5;
									}
									
								}
								
							break;
							
							default:
							break;
						} // switch key.code
						
					} //switch keyPressed
					break;
				
				default :
				break;
				
				} // Switch des évènements
				
			} // Boucle des évènements
	}
	
	return action;
}
