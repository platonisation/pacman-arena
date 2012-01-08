#include "Party.h"

Party::Party ( ) :
	_status ( WAITING ),
	_map_name ( "" ),
	_map ( std::vector < std::vector < unsigned char > > ( ) ),
	_chars ( std::vector < Character > ( ) ),
	_timer ( 0.f ),
	_slot ( 0 )
{
	
}

Party::Party ( const std::string& map_name, const float timer, const unsigned char slot ) :
	_status ( WAITING ),
	_map_name ( map_name ),
	_map ( std::vector < std::vector < unsigned char > > ( ) ),
	_chars ( std::vector < Character > ( ) ),
	_timer ( timer ),
	_slot ( slot )
{
	
	changeMap ( _map_name );
	
}

Party::~Party ( )
{
	
}

void Party::changeMap ( const std::string& map )
{
	
	// Charger une carte
	
	
}

std::vector < Character > Party::getChars ( ) const { return _chars ; }
unsigned char Party::getStatus ( ) const { return _status ; }
unsigned char Party::getCase ( const int x, const int y ) const { return WALL ; } /* A faire */
float Party::getTimer ( ) const { return _timer ; }
unsigned char Party::getSlot ( ) const { return _slot ; }

void Party::setChars ( const std::vector < Character >& chars ) { _chars = chars ; }
void Party::setStatus ( const unsigned char status ) { _status = status ; }
void Party::setCase ( const int x, const int y, const unsigned char case_status ) { /* A faire */ }
void Party::setTimer ( const float timer ) { _timer = timer ; }
void Party::setSlot ( const unsigned char slot ) { _slot = slot ; }
