#include <cstdlib>
#include <vector>
#include <string>
#include "Character.h"

class Party
{
	
	private :
		unsigned char _status ;
		std::string _map_name ;
		std::vector < std::vector < unsigned char > > _map ;
		std::vector < Character > _chars ;
		float _timer ;
		
		unsigned char _slot ;
		
	public :
		static const unsigned char WAITING = 0 ;
		static const unsigned char PLAYING = 1 ;
		static const unsigned char ENDED = 2 ;
		
		static const unsigned char VOID = 0 ;
		static const unsigned char WALL = 1 ;
		static const unsigned char PAC_POINT = 2 ;
		static const unsigned char SUPERPAC_POINT = 3 ;
		
		Party ( ) ;
		Party ( const std::string& map_name, const float timer, const unsigned char slot ) ;
		~Party ( ) ;
		
		void changeMap ( const std::string& map ) ;
		
		std::vector < Character > getChars ( ) const ;
		unsigned char getStatus ( ) const ;
		unsigned char getCase ( const int x, const int y ) const ;
		float getTimer ( ) const ;
		unsigned char getSlot ( ) const ;
		
		void setChars ( const std::vector < Character >& chars ) ;
		void setStatus ( const unsigned char status ) ;
		void setCase ( const int x, const int y, const unsigned char case_status ) ;
		void setTimer ( const float timer ) ;
		void setSlot ( const unsigned char slot ) ;
		
} ;
