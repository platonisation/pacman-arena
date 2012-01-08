#include "Party.h"
#include <fstream>

const unsigned char Party::WAITING = 0 ;
const unsigned char Party::PLAYING = 1 ;
const unsigned char Party::ENDED = 2 ;

const unsigned char Party::VOID = 0 ;
const unsigned char Party::WALL = 1 ;
const unsigned char Party::PAC_POINT = 2 ;
const unsigned char Party::SUPERPAC_POINT = 3 ;

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
	std::ifstream myfile ( map.c_str ( ) ) ;
	
	if ( myfile.is_open ( ) )
	{
		
		int width, height ;
		
		myfile >> width >> height ;
		
		_map.resize ( width ) ;
		for ( int i = 0 ; i < width ; i ++ )
		{
			
			_map[i].resize ( height ) ;
			for ( int j = 0 ; j < height ; j ++ )
				_map[i][j] = WALL ;
			
		}
		
		int x, y, type ;
		
		while ( myfile.good ( ) )
		{
			
			myfile >> x >> y >> type ;
			_map[x][y] = type ;
			
		}
		
		myfile.close ( ) ;
		
	}
	else
	{
		
		_map_name = "" ;
		_map = std::vector < std::vector < unsigned char > > ( ) ;
		
	}
	
}

std::vector < Character > Party::getChars ( ) const { return _chars ; }
unsigned char Party::getStatus ( ) const { return _status ; }
unsigned char Party::getCase ( const unsigned int x, const unsigned int y ) const { return ( x <= getWidth ( ) && y <= getHeight ( ) ) ? _map[x][y] : VOID ; }
float Party::getTimer ( ) const { return _timer ; }
unsigned char Party::getSlot ( ) const { return _slot ; }

unsigned int Party::getWidth ( ) const { return _map.size ( ) ; }
unsigned int Party::getHeight ( ) const { return _map[0].size ( ) ; }

void Party::setChars ( const std::vector < Character >& chars ) { _chars = chars ; }
void Party::setStatus ( const unsigned char status ) { _status = status ; }
void Party::setCase ( const unsigned int x, const unsigned int y, const unsigned char case_status ) { if ( x <= getWidth ( ) && y <= getHeight ( ) ) _map[x][y] = case_status ; }
void Party::setTimer ( const float timer ) { _timer = timer ; }
void Party::setSlot ( const unsigned char slot ) { _slot = slot ; }
