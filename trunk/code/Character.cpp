#include "Character.h"

Character::Character ( const unsigned float x, const unsigned float y, const unsigned int point, const unsigned char status, const unsigned char moving, const unsigned char orientation ) :
	_x ( x ),
	_y ( y ),
	_point ( point ),
	_status ( status ),
	_moving ( moving ),
	_orientation ( orientation )
{
	
}

Character::~Character ( )
{
	
}

unsigned float Character::getX ( ) const { return _x ; }
unsigned float Character::getY ( ) const { return _y ; }
unsigned int getPoint ( ) const { return _point ; }
unsigned char Character::getStatus ( ) const { return _status ; }
unsigned char Character::getMoving ( ) const { return _moving ; }
unsigned char Character::getOrientation ( ) const { return _orientation; }

void Character::setX ( const unsigned float x ) { _x = x ; }
void Character::setY ( const unsigned float y ) { _y = y ; }
void setPoint ( const unsigned int point ) const { _point = point ; }
void Character::setStatus ( const unsigned char status ) { _status = status ; }
void Character::setMoving ( const unsigned char moving ) { _moving = moving ; }
unsigned char Character::getOrientation ( const unsigned char orientation ) const { _orientation = _orientation ; }
