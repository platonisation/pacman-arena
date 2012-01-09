#include <SFML/Network.hpp>
#include "Party.h"

// Pour récupérer ou envoyer une requête
sf::Packet& operator << ( sf::Packet& Packet, const Query& q ) ;
sf::Packet& operator >> ( sf::Packet& Packet, Query& q ) ;

// Pour récupérer ou envoyer une réponse
sf::Packet& operator << ( sf::Packet& Packet, const Response& p ) ;
sf::Packet& operator >> ( sf::Packet& Packet, Response& p ) ;
