#ifndef __ACTION_H__

#define __ACTION_H__
#include <SFML/Graphics.hpp>
#include "myOption.h"

int menu ( sf::RenderWindow& window, myOption& opt ) ;
int option ( sf::RenderWindow& window, myOption& opt ) ;
int create ( sf::RenderWindow& window, myOption& opt ) ; // Socket à rajouter
int join ( sf::RenderWindow& window, myOption& opt ) ; // Socket à rajouter
int play ( sf::RenderWindow& window, myOption& opt ) ; // Socket à rajouter

#endif
