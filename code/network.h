#ifndef __NETWORK_H__

#define __NETWORK_H__
#include <SFML/Network.hpp>
#include "Party.h"

// Pour récupérer ou envoyer une requête
sf::Packet& operator << ( sf::Packet& Pck, const Party& p ) ;
sf::Packet& operator >> ( sf::Packet& Pck, Party& p ) ;

sf::Packet& operator << ( sf::Packet& Pck, const Character& c ) ;
sf::Packet& operator >> ( sf::Packet& Pck, Character& c ) ;

#endif
