#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "myOption.h"
#include "action.h"

using namespace sf ;

int main ( int argc, char *argv[] )
{
	
    // Ouverture de la fenêtre avec la SMFL
    RenderWindow window ( VideoMode ( 800, 600, 32 ), "Pacman Arena" ) ;
	
    // Déclaration des variables
    int action = 1 ;
    myOption opt = myOption ( ) ;
	
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
	
    // Fermeture de la fenêtre SFML
    window.Close ( ) ;
	
    return EXIT_SUCCESS ;
    
}
