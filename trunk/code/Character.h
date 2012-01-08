class Character
{
	
	private :
		unsigned float _x ;
		unsigned float _y ;
		
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
		
		Character ( const unsigned float x = 0.f, const unsigned float y = 0.f, const unsigned int point = 0, const unsigned char status = GHOST, const unsigned char moving = NONE, const unsigned char orientation = NORTH ) ;
		~Character ( ) ;
		
		unsigned float getX ( ) const ;
		unsigned float getY ( ) const ;
		unsigned int getPoint ( ) const ;
		unsigned char getStatus ( ) const ;
		unsigned char getMoving ( ) const ;
		unsigned char getOrientation ( ) const ;
		
		void setX ( const unsigned float x ) ;
		void setY ( const unsigned float y ) ;
		void setPoint ( const unsigned int point ) const ;
		void setStatus ( const unsigned char status ) ;
		void setMoving ( const unsigned char moving ) ;
		unsigned char getOrientation ( const unsigned char orientation ) const ;
		
} ;
