#include "Party.h"
#include <fstream>
#include <iostream>

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
	_chars ( NULL ),
	_timer ( 0.f ),
	_msg ( "" ),
	_slot ( 0 )
{
	
}

Party::Party ( const std::string& map_name, const float timer, const unsigned char slot ) :
	_status ( WAITING ),
	_map_name ( map_name ),
	_map ( std::vector < std::vector < unsigned char > > ( ) ),
	_chars ( NULL ),
	_timer ( timer ),
	_msg ( "" ),
	_slot ( slot )
{
	
	_chars = new Character* [_slot] ;
	
	for ( unsigned char i = 0 ; i < _slot ; i ++ )
		_chars[i] = NULL ;
	
	changeMap ( _map_name );
	
}

Party::~Party ( )
{
	
	for ( unsigned char i = 0 ; i < _slot ; i ++ )
		delete _chars[i] ;
	
	delete[] _chars ;
	delete[] _spawns ;
	
}

void Party::changeMap ( const std::string& map ) throw ( std::string )
{
	
	// Charger une carte
	std::ifstream myfile ( map.c_str ( ) ) ;
	
	if ( myfile.is_open ( ) )
	{
		
		// On récupère la taille de la carte et le nombre de spawn
		int width, height, o1, o2 ;
		
		myfile >> width >> height >> o1 ;
		
		_nb_spawns = static_cast < unsigned char > ( o1 ) ;
		
		_map.resize ( width ) ;
		for ( int i = 0 ; i < width ; i ++ )
		{
			
			_map[i].resize ( height ) ;
			for ( int j = 0 ; j < height ; j ++ )
				_map[i][j] = WALL ;
			
		}
		
		// On récupère la position des différents spawn
		_spawns = new std::pair < unsigned char, unsigned char >[_nb_spawns] ;
		
		for ( int i = 0 ; i < _nb_spawns ; i ++ )
		{
			
			myfile >> o1 >> o2 ;
			_spawns[i].first = static_cast < unsigned char > ( o1 ) ;
			_spawns[i].second = static_cast < unsigned char > ( o2 ) ;
			
		}
		
		// On récupère les cases de la carte
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
		
		throw std::string ( "Carte introuvable" ) ;
		
	}
	
}

Character** Party::getChars ( ) const { return _chars ; }
unsigned char Party::getStatus ( ) const { return _status ; }
unsigned char Party::getCase ( const unsigned char x, const unsigned char y ) const { return ( x < getWidth ( ) && y < getHeight ( ) ) ? _map[x][y] : VOID ; }
float Party::getTimer ( ) const { return _timer ; }
unsigned char Party::getSlot ( ) const { return _slot ; }
std::string Party::getMapName ( ) const { return _map_name ; }
std::string Party::getMessage ( ) const { return _msg ; }
std::pair < unsigned char, std::pair < unsigned char, unsigned char >* > Party::getSpawns ( ) const { return std::pair < unsigned char, std::pair < unsigned char, unsigned char >* > ( _nb_spawns, _spawns ) ; }

unsigned int Party::getWidth ( ) const { return _map.size ( ) ; }
unsigned int Party::getHeight ( ) const { return _map[0].size ( ) ; }

void Party::setChars ( Character** const c ) { _chars = c ; }
void Party::setStatus ( const unsigned char status ) { _status = status ; }
void Party::setCase ( const unsigned int x, const unsigned int y, const unsigned char case_status ) { if ( x < getWidth ( ) && y < getHeight ( ) ) _map[x][y] = case_status ; }
void Party::setTimer ( const float timer ) { _timer = timer ; }
void Party::setSlot ( const unsigned char slot ) { _slot = slot ; }
void Party::setMessage ( const std::string& msg ) { _msg = msg ; }
