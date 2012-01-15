#include "Character.h"

const unsigned char Character::GHOST = 0 ;
const unsigned char Character::PACMAN = 1 ;
const unsigned char Character::SUPER_PACMAN = 2 ;

const unsigned char Character::NONE = 0 ;
const unsigned char Character::NORTH = 1 ;
const unsigned char Character::EAST = 2 ;
const unsigned char Character::SOUTH = 3 ;
const unsigned char Character::WEST = 4 ;

Character::Character ( ) :
	_name ( "Player" ),
	_x ( 0.f ),
	_y ( 0.f ),
	_point ( 0 ),
	_status ( GHOST ),
	_moving ( NONE ),
	_wish ( NONE ),
	_orientation ( WEST ),
	_timer ( )
{
	
}

Character::Character ( const std::string& name, const float x, const float y, const unsigned int point, const unsigned char status, const unsigned char moving, const unsigned char orientation ) :
	_name ( name ),
	_x ( x ),
	_y ( y ),
	_point ( point ),
	_status ( status ),
	_moving ( moving ),
	_wish ( NONE ),
	_orientation ( orientation ),
	_timer ( )
{
	
}

Character::~Character ( )
{
	
}

std::string Character::getName ( ) const { return _name ; }
float Character::getX ( ) const { return _x ; }
float Character::getY ( ) const { return _y ; }
unsigned int Character::getPoint ( ) const { return _point ; }
unsigned char Character::getStatus ( ) const { return _status ; }
unsigned char Character::getMoving ( ) const { return _moving ; }
unsigned char Character::getWish ( ) const { return _wish ; }
unsigned char Character::getOrientation ( ) const { return _orientation ; }
float Character::getTimer ( ) const { return _timer.GetElapsedTime ( ) ; }

void Character::setName ( const std::string& name ) { _name = name ; }
void Character::setX ( const float x ) { _x = x ; }
void Character::setY ( const float y ) { _y = y ; }
void Character::setPoint ( const unsigned int point ) { _point = point ; }
void Character::setStatus ( const unsigned char status ) { _status = status ; }
void Character::setMoving ( const unsigned char moving ) { _moving = moving ; }
void Character::setWish ( const unsigned char wish ) { _wish = wish ; }
void Character::setOrientation ( const unsigned char orientation ) { _orientation = orientation ; }
void Character::resetTimer ( ) { _timer.Reset ( ) ; }
