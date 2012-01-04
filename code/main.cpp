#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 500, SCREEN_BPP = 32 ;

int main ( int argc, char *argv[] )
{
	
	// Ouverture de la fenêtre avec la SMFL
	RenderWindow window ( VideoMode ( 800, 600, 32 ), "Ma premiere fenetre SFML ! " ) ;
	
	// Déclaration des variables
	int action = 1 ;
	//Option opt = Option ( ) ;
	
	while ( action != 0 )
	{
		
		switch ( action )
		{
		
			case 1 :
				// Menu
				action = menu ( window ) ;
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
