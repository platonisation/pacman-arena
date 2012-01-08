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
		static const unsigned char WAITING ;
		static const unsigned char PLAYING ;
		static const unsigned char ENDED ;
		
		static const unsigned char VOID ;
		static const unsigned char WALL ;
		static const unsigned char PAC_POINT ;
		static const unsigned char SUPERPAC_POINT ;
		
		Party ( ) ;
		Party ( const std::string& map_name, const float timer, const unsigned char slot ) ;
		~Party ( ) ;
		
		void changeMap ( const std::string& map ) ;
		
		std::vector < Character > getChars ( ) const ;
		unsigned char getStatus ( ) const ;
		unsigned char getCase ( const unsigned int x, const unsigned int y ) const ;
		float getTimer ( ) const ;
		unsigned char getSlot ( ) const ;
		
		unsigned int getWidth ( ) const ;
		unsigned int getHeight ( ) const ;
		
		void setChars ( const std::vector < Character >& chars ) ;
		void setStatus ( const unsigned char status ) ;
		void setCase ( const unsigned int x, const unsigned int y, const unsigned char case_status ) ;
		void setTimer ( const float timer ) ;
		void setSlot ( const unsigned char slot ) ;
		
} ;
