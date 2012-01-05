#include "myOption.h"

using namespace sf ;

myOption::myOption ( )
{
	
	this->up = Key::Up ;
	this->down = Key::Down ;
	this->left = Key::Left ;
	this->right = Key::Right ;
	this->valid = Key::Return ;
	this->cancel = Key::Escape ;
	
}

myOption::~myOption ( ) { }

Key::Code myOption::getUpKey ( ) { return this->up ; }
Key::Code myOption::getDownKey ( ) { return this->down ; }
Key::Code myOption::getLeftKey ( ) { return this->left ; }
Key::Code myOption::getRightKey ( ) { return this->right ; }
Key::Code myOption::getValidKey ( ) { return this->valid ; }
Key::Code myOption::getCancelKey ( ) { return this->cancel ; }

void myOption::setUpKey ( Key::Code key ) { this->up = key ; }
void myOption::setDownKey ( Key::Code key ) { this->down = key ; }
void myOption::setLeftKey ( Key::Code key ) { this->left = key ; }
void myOption::setRightKey ( Key::Code key ) { this->right = key ; }
void myOption::setValidKey ( Key::Code key ) { this->valid = key ; }
void myOption::setCancelKey ( Key::Code key ) { this->cancel = key ; }
