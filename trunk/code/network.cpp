#include "network.h"

sf::Packet& operator << ( sf::Packet& Pck, const Party& p )
{
	
	Pck
		<< p.getStatus ( )
		<< p.getMapName ( )
		<< p.getMessage ( )
		<< p.getTimer ( )
		<< p.getSlot ( ) ;
	
	Character** chars = p.getChars ( ) ;
	
	for ( unsigned char i = 0 ; i < p.getSlot ( ) ; i ++ )
	{
		
		if ( chars[i] == NULL )
			Pck << static_cast < unsigned char > ( 0 ) ;
		else
			Pck << static_cast < unsigned char > ( 1 ) << *( chars[i] ) ;
		
	}
	
	Pck
		<< p.getWidth ( )
		<< p.getHeight ( ) ;
	
	for ( unsigned char i = 0 ; i < p.getWidth ( ) ; i ++ )
	{
		
		for ( unsigned char j = 0 ; j < p.getHeight ( ) ; j ++ )
		{
			
			Pck << p.getCase ( i, j ) ;
			
		}
		
	}
	
	return Pck ;
	
}

sf::Packet& operator << ( sf::Packet& Pck, const Character& c )
{
	
	Pck
		<< c.getName ( )
		<< c.getX ( )
		<< c.getY ( )
		<< c.getPoint ( )
		<< c.getStatus ( )
		<< c.getStatus ( )
		<< c.getMoving ( )
		<< c.getOrientation ( ) ;
	
	return Pck ;
	
}

sf::Packet& operator >> ( sf::Packet& Pck, Party& p )
{
	
	unsigned char c, c2 ;
	std::string str ;
	float f ;
	
	Pck >> c ;
	p.setStatus ( c ) ;
	
	Pck >> str ;
	if ( str != p.getMapName ( ) )
		p.changeMap ( str ) ;
	
	Pck >> str ;
	p.setMessage ( str ) ;
	
	Pck >> f ;
	p.setTimer ( f ) ;
	
	
	c2 = p.getSlot ( ) ;
	Pck >> c ;
	p.setSlot ( c ) ;
	
	/*
	if ( c != c2 )
	
	Character** chars = p.getChars ( ) ;
	
	for ( unsigned char i = 0 ; i < p.getSlot ( ) ; i ++ )
	{
		
		if ( chars[i] == NULL )
			Pck << 0 ;
		else
			Pck << 1 << *( chars[i] ) ;
		
	}
	
	Pck
		<< p.getWidth ( )
		<< p.getHeight ( ) ;
	
	for ( unsigned char i = 0 ; i < p.getWidth ( ) ; i ++ )
	{
		
		for ( unsigned char j = 0 ; j < p.getHeight ( ) ; j ++ )
		{
			
			Pck << p.getCase ( i, j ) ;
			
		}
		
	}*/
	
	return Pck ;
	
}

sf::Packet& operator >> ( sf::Packet& Pck, Character& c )
{
	
	return Pck ;
	
}
