#include <cstdlib>
#include <vector>
#include <string>
#include <utility>
#include "Character.h"

class Party
{
	
	private :
		unsigned char _status ;
		std::string _map_name ;
		std::vector < std::vector < unsigned char > > _map ;
		std::pair < unsigned char, Character* > _chars ;
		float _timer ;
		std::string _msg ;
		
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
		
		std::pair < unsigned char, Character* > getChars ( ) const ;
		unsigned char getStatus ( ) const ;
		unsigned char getCase ( const unsigned int x, const unsigned int y ) const ;
		float getTimer ( ) const ;
		unsigned char getSlot ( ) const ;
		std::string getMapName ( ) const ;
		std::string getMessage ( ) const ;
		
		unsigned int getWidth ( ) const ;
		unsigned int getHeight ( ) const ;
		
		void setChars ( const std::pair < unsigned char, Character* >& chars ) ;
		void setStatus ( const unsigned char status ) ;
		void setCase ( const unsigned int x, const unsigned int y, const unsigned char case_status ) ;
		void setTimer ( const float timer ) ;
		void setSlot ( const unsigned char slot ) ;
		void setMessage ( const std::string& msg ) ;
		
} ;
