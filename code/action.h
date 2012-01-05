#ifndef __ACTION_H__

#define __ACTION_H__
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "myOption.h"

int menu ( sf::RenderWindow& window, myOption& opt ) ;
int option ( sf::RenderWindow& window, myOption& opt ) ;
int create ( sf::RenderWindow& window, myOption& opt, sf::SocketTCP& sck ) ;
int join ( sf::RenderWindow& window, myOption& opt, sf::SocketTCP& sck ) ;
int play ( sf::RenderWindow& window, myOption& opt, sf::SocketTCP& sck ) ;

#endif
