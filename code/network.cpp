#include "network.h"
#include <iostream>

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
	
	// On compte le nombre de case à envoyer
	unsigned int cpt = 0 ;
	for ( unsigned int i = 0 ; i < p.getWidth ( ) ; i ++ )
		for ( unsigned int j = 0 ; j < p.getHeight ( ) ; j ++ )
			if ( p.getCase ( i, j ) != Party::WALL )
				cpt ++ ;
	
	Pck << cpt ;
	
	// Puis on les envoie
	for ( unsigned int i = 0 ; i < p.getWidth ( ) ; i ++ )
		for ( unsigned int j = 0 ; j < p.getHeight ( ) ; j ++ )
			if ( p.getCase ( i, j ) != Party::WALL )
				Pck << i << j << p.getCase ( i, j ) ;
	
	return Pck ;
	
}

sf::Packet& operator << ( sf::Packet& Pck, const Character& c )
{
	
	Pck
		<< c.getName ( )
		<< c.getX ( )
		<< c.getY ( )
		<< c.getPoint ( )
		<< static_cast < unsigned int > ( c.getStatus ( ) )
		<< static_cast < unsigned int > ( c.getMoving ( ) )
		<< static_cast < unsigned int > ( c.getOrientation ( ) ) ;
	
	return Pck ;
	
}

sf::Packet& operator >> ( sf::Packet& Pck, Party& p ) throw ( std::string )
{
	
	unsigned char c, c2 ;
	unsigned int cpt, x, y ;
	std::string str ;
	float f ;
	
	Pck >> c ;
	p.setStatus ( c ) ;
	
	try
	{
		
		Pck >> str ;
		if ( str != p.getMapName ( ) )
			p.changeMap ( str ) ;
			
	}
	catch ( std::string excep )
	{
		
		throw excep ;
		
	}
	
	Pck >> str ;
	p.setMessage ( str ) ;
	
	Pck >> f ;
	p.setTimer ( f ) ;
	
	c2 = p.getSlot ( ) ;
	Pck >> c ;
	p.setSlot ( c ) ;
	
	Character** chars ;
	
	// Il s'agit du premier update de la part du client, il faut allouer le tableau de personnage
	if ( c != c2 )
	{
		
		chars = new Character*[c] ;
		
		for ( unsigned char i = 0 ; i < p.getSlot ( ) ; i ++ )
			chars[i] = NULL ;
		
		p.setChars ( chars ) ;
			
	}
	
	chars = p.getChars ( ) ;
	
	for ( unsigned char i = 0 ; i < p.getSlot ( ) ; i ++ )
	{
		
		Pck >> c ;
		
		// Le personnage n'existe pas ou plus
		if ( c == 0 )
		{
			
			if ( chars[i] != NULL )
				delete chars[i] ;
				
			chars[i] = NULL ;
			
		}
		// Le personnage existe
		else
		{
			
			if ( chars[i] == NULL )
				chars[i] = new Character ;
			
			Pck >> *( chars[i] ) ;
			
		}
		
	}
	
	// On récupère le nombre de case que le serveur nous a envoyées
	Pck >> cpt ;
	
	while ( cpt > 0 )
	{
		
		Pck >> x >> y >> c ;
		p.setCase ( x, y, c ) ;
		
		cpt -- ;
		
	}
	
	return Pck ;
	
}

sf::Packet& operator >> ( sf::Packet& Pck, Character& c )
{
	
	std::string str ;
	float f ;
	unsigned int i ;
	
	Pck >> str ;
	c.setName ( str ) ;
	
	Pck >> f ;
	c.setX ( f ) ;
	
	Pck >> f ;
	c.setY ( f ) ;
	
	Pck >> i ;
	c.setPoint ( i ) ;
	
	Pck >> i ;
	c.setStatus ( static_cast < unsigned char > ( i ) ) ;
	
	Pck >> i ;
	c.setMoving ( static_cast < unsigned char > ( i ) ) ;
	
	Pck >> i ;
	c.setOrientation ( static_cast < unsigned char > ( i ) ) ;
	
	return Pck ;
	
}
