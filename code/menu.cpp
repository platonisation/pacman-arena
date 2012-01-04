#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "action.h"

using namespace sf;

int menu ( RenderWindow window, myOption& opt )
{
	bool quitter = false;
	int action = 0; 
	while( !quitter )
	{
		/* Chargement des images necessaires */
		
		
		Event event;
		while (app.GetEvent(event)) // Boucle des évènements
		{
			switch (event.Type) // Type de l'évènement en attente :
			{
				case Event::Closed : // Croix en haut à droite
					action = 0;
					quitter = true;
					break;

				case Event::KeyPressed : // Appui sur une touche du clavier
				{

					if ( opt.getUpKey() )
					{
						// choix ++
						/* on augmente la selection de x pixels */
					}
					else if ( opt.getLeftKey() )
					{
						// choix ++
						/* on augmente la selection de x pixels */
					}
					else if ( opt.getRightKey() )
					{
						//choix --
						/* on diminue la selection de x pixels */
					}
					else if ( opt.getDownKey() )
					{
						// choix --
						/* on augmente la selection de x pixels */
					}
					else if ( opt.getValidKey() )
					{
						// goto
						/* appel de la fonction necessaire */
					}
					
				}
				break;

				default :
					break
			}
		}
	}
	return action;
}
