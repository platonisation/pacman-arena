#include <vector>
#include <string>
#include "Character.h"

class Party
{
	
	private :
		unsigned char status ;
		vector < vector < unsigned char > > map ;
		vector < Character > chars ;
		
	public :
		static const unsigned char WAITING = 0 ;
		static const unsigned char PLAYING = 1 ;
		static const unsigned char ENDED = 2 ;
		
		static const unsigned char VOID = 0 ;
		static const unsigned char WALL = 1 ;
		static const unsigned char PAC_POINT = 2 ;
		static const unsigned char SUPERPAC_POINT = 3 ;
		
		Party ( ) ;
		Party ( const std::string& map ) ;
		~Party ( ) ;
		
		void changeMap ( const std::string& map ) ;
		
		vector < Character > getChars ( ) const ;
		unsigned char getStatus ( ) const ;
		unsigned char getCase ( const int x, const int y ) const ;
		
		void setChars ( const vector < Character >& Chars ) ;
		void setStatus ( const unsigned char status ) ;
		void setCase ( const int x, const int y, const unsigned char case_status ) ;
		
} ;
