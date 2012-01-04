#ifndef __MYOPTION_H__

#define __MYOPTION_H__
#include <SFML/Window/Event.hpp>

class myOption
{
	
	private :
		sf::Key::Code up ;
		sf::Key::Code down ;
		sf::Key::Code left ;
		sf::Key::Code right ;
		sf::Key::Code valid ;
		sf::Key::Code cancel ;
	
	public :
		myOption ( ) ;
		~myOption ( ) ;
	
		sf::Key::Code getUpKey ( ) ;
		sf::Key::Code getDownKey ( ) ;
		sf::Key::Code getLeftKey ( ) ;
		sf::Key::Code getRightKey ( ) ;
		sf::Key::Code getValidKey ( ) ;
		sf::Key::Code getCancelKey ( ) ;
	
		void setUpKey ( sf::Key::Code key ) ;
		void setDownKey ( sf::Key::Code key ) ;
		void setLeftKey ( sf::Key::Code key ) ;
		void setRightKey ( sf::Key::Code key ) ;
		void setValidKey ( sf::Key::Code key ) ;
		void setCancelKey ( sf::Key::Code key ) ;
	
} ;

#endif
