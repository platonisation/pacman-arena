#ifndef __MYOPTION_H__

#define __MYOPTION_H__
//#include <SFML/Event.hpp>

public class myOption
{
	
	public myOption ( ) ;
	public ~myOption ( ) ;
	
	public sf::Key::Code getUpKey ( ) ;
	public sf::Key::Code getDownKey ( ) ;
	public sf::Key::Code getLeftKey ( ) ;
	public sf::Key::Code getRightKey ( ) ;
	public sf::Key::Code getValidKey ( ) ;
	public sf::Key::Code getCancelKey ( ) ;
	
}

#endif
