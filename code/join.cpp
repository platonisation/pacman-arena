#include <cstdlib>
#include <iostream>
#include <SFML/System.hpp>
#include <string>

#include "action.h"

using namespace sf;

std::string askIpAdress(sf::RenderWindow& window, int &action);

int join ( sf::RenderWindow& window, myOption& opt, sf::SocketTCP& sck ) 
{
	int action = 0 ;
	
	sf::SocketTCP Client;
	if (Client.Connect(4567, "192.168.0.2") != sf::Socket::Done)
	{
		// Error...
	}

	char Buffer[] = "Hi guys !";
	if (Client.Send(Buffer, sizeof(Buffer)) != sf::Socket::Done)
	{
		// Error...
	}

	char buffer[128];
	std::size_t Received;
	if (Client.Receive(Buffer, sizeof(buffer), Received) != sf::Socket::Done)
	{
		// Error...
	}
	
	return action;
}

std::string askIpAdress(sf::RenderWindow& window, int &action )
{
	sf::Shape Rect = sf::Shape::Rectangle((window.GetWidth()-200)/2,(window.GetHeight()-40)/2 , (window.GetWidth()+200)/2,(window.GetHeight()+40)/2 , Color(0,0,0,0), 5.f, Color::White);
	
	bool quitter = false;
	std::string ip;
	String ipDraw;
	ipDraw.SetColor(Color::White);
	ipDraw.SetPosition ( (window.GetWidth()-190)/2, (window.GetHeight()-35)/2 );
	
	while( !quitter )
	{
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
						if(event.Key.Code <= Key::Num9 || event.Key.Code >= Key::Num0 ) // Si on tape un chiffre en 0 et 9
						{
							ip += static_cast<char>(event.Key.Code);
							ipDraw.SetText(ip);
							window.Draw(ipDraw);
						}
						switch(event.Key.Code)
						{
							case Key::Period:  // touche .
							
							break;
							case Key::Back:   
								if(ip.size() > 0)
									quitter == true;
								else
									ip = ip.erase(ip.size(),-1);// supprime le dernier charactere
							break;
							case Key::Delete:
								ip = ip.erase(ip.size()-1,1);// supprime le dernier charactere
							break;
							case Key::Return:   // touche entrées
								quitter=true;
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
	return ip;
	
}
