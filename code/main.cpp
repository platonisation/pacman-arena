#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "myOption.h"
#include "action.h"

using namespace sf;

int main ( int argc, char *argv[] )
{
	
	// Ouverture de la fenêtre avec la SMFL
	RenderWindow window ( VideoMode ( 800, 600, 32 ), "Ma premiere fenetre SFML ! " ) ;
	
	// Déclaration des variables
	int action = 1 ;
	//myOption opt = myOption ( ) ;
	
	while ( action != 0 )
	{
		
		switch ( action )
		{
		
			case 1 :
				// Menu
				action = menu ( window, opt ) ;
				break ;
				
			default :
				action = 0 ;
				break ;
				
		}
		
	}
	
	// Libération de la mémoire
	// ...
	
	// Fermeture de la SDL
	window.Close ( ) ;
	
	return EXIT_SUCCESS;
}
