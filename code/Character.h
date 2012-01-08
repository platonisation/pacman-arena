#include <string>

class Character
{
	
	private :
		bool _online ; 
		std::string _name ;
		float _x ;
		float _y ;
		
		unsigned int _point ;
		
		unsigned char _status ;
		unsigned char _moving ;
		unsigned char _orientation ;
		
	public :
		static const unsigned char GHOST = 0 ;
		static const unsigned char PACMAN = 1 ;
		static const unsigned char SUPER_PACMAN = 2 ;
		
		static const unsigned char NONE = 0 ;
		static const unsigned char NORTH = 1 ;
		static const unsigned char EAST = 2 ;
		static const unsigned char SOUTH = 3 ;
		static const unsigned char WEST = 4 ;
		
		Character ( ) ;
		Character ( const bool connected, const std::string& name, const float x = 0.f, const float y = 0.f, const unsigned int point = 0, const unsigned char status = GHOST, const unsigned char moving = NONE, const unsigned char orientation = NORTH ) ;
		~Character ( ) ;
		
		float getX ( ) const ;
		float getY ( ) const ;
		unsigned int getPoint ( ) const ;
		unsigned char getStatus ( ) const ;
		unsigned char getMoving ( ) const ;
		unsigned char getOrientation ( ) const ;
		
		void setX ( const float x ) ;
		void setY ( const float y ) ;
		void setPoint ( const unsigned int point ) ;
		void setStatus ( const unsigned char status ) ;
		void setMoving ( const unsigned char moving ) ;
		void getOrientation ( const unsigned char orientation ) ;
		
} ;