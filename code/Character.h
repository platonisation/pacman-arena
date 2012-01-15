#ifndef __CHARACTER_H__

#define __CHARACTER_H__
#include <string>
#include <SFML/System/Clock.hpp>

class Character
{
	
	private :
		std::string _name ;
		float _x ;
		float _y ;
		
		unsigned int _point ;
		
		unsigned char _status ;
		unsigned char _moving ;
		unsigned char _wish ;
		unsigned char _orientation ;
		
		sf::Clock _timer ;
		
	public :
		static const unsigned char GHOST ;
		static const unsigned char PACMAN ;
		static const unsigned char SUPER_PACMAN ;
		
		static const unsigned char NONE ;
		static const unsigned char NORTH ;
		static const unsigned char EAST ;
		static const unsigned char SOUTH ;
		static const unsigned char WEST ;
		
		Character ( ) ;
		Character ( const std::string& name, const float x = 0.f, const float y = 0.f, const unsigned int point = 0, const unsigned char status = GHOST, const unsigned char moving = NONE, const unsigned char orientation = NORTH ) ;
		~Character ( ) ;
		
		std::string getName ( ) const ;
		float getX ( ) const ;
		float getY ( ) const ;
		unsigned int getPoint ( ) const ;
		unsigned char getStatus ( ) const ;
		unsigned char getMoving ( ) const ;
		unsigned char getWish ( ) const ;
		unsigned char getOrientation ( ) const ;
		float getTimer ( ) const ;
		
		void setName ( const std::string& name ) ;
		void setX ( const float x ) ;
		void setY ( const float y ) ;
		void setPoint ( const unsigned int point ) ;
		void setStatus ( const unsigned char status ) ;
		void setMoving ( const unsigned char moving ) ;
		void setWish ( const unsigned char wish ) ;
		void setOrientation ( const unsigned char orientation ) ;
		void resetTimer ( ) ;
		
} ;

#endif
