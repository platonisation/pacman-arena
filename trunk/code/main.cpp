#include <cstdlib>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "myOption.h"
#include "action.h"

using namespace sf ;

int main ( int argc, char *argv[] )
{
	
	// Analyse des paramètres
	bool debug = false ;
	
	if ( argc > 1 )
	{
		
		for ( int i = 1 ; i < argc ; i ++ )
		{
			
			std::string arg ( argv[i] ) ;
			if ( arg == "-v" || arg == "DEBUG" )
				debug = true ;
			
		}	
		
	}
	
    // Ouverture de la fenêtre avec la SMFL et création du socket
    RenderWindow window ( VideoMode ( 800, 600, 32 ), "Pacman Arena" ) ;
    SocketTCP sck ( ) ;
	
    // Déclaration des variables
    int action = 1 ;
    myOption opt = myOption ( debug ) ;
	
    while ( action != 0 )
    {
		
        switch ( action )
        {
			
        case 1 :
            // Menu
            if ( opt.getDebug ( ) ) std::cout << "Ouverture Menu" << std::endl ;
            action = menu ( window, opt ) ;
            break ;
			
		case 2 :
			// Option
			if ( opt.getDebug ( ) ) std::cout << "Ouverture Option" << std::endl ;
			action = 1 ;
			break ;
			
		case 3 :
			// Créer
			if ( opt.getDebug ( ) ) std::cout << "Ouverture Créer" << std::endl ;
			action = 1 ;
			break ;
			
		case 4 :
			// Rejoindre
			if ( opt.getDebug ( ) ) std::cout << "Ouverture Rejoindre" << std::endl ;
			action = join (window, opt, sck );
			break ;
		
		case 5 :
			// En jeu
			if ( opt.getDebug ( ) ) std::cout << "Ouverture Jouer" << std::endl ;
			action = 1 ;
			break ;
			
        default :
			if ( opt.getDebug ( ) ) std::cout << "Action inconnue" << std::endl ;
            action = 0 ;
            break ;
			
        }
		
    }
	
    // Fermeture de la fenêtre SFML
    window.Close ( ) ;
	
	if ( opt.getDebug ( ) ) std::cout << "Fermeture" << std::endl ;
	
    return EXIT_SUCCESS ;
    
}
