#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "action.h"

using namespace sf;

bool loadImage();

int menu ( RenderWindow window, myOption& opt )
{
    bool quitter = false;
    int action = 3;

    /* Chargement des images necessaires */

    if(!loadImage())
    {
        //en cas de pépin ( image non dispo )
        return 0;
    }

    while( !quitter )
    {
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
                    action += 1;
                    if(action <= 3)
                        action = 3;
                    /* on augmente la selection de x pixels */
                }
                else if ( opt.getLeftKey() )
                {
                    action += 1;
                    if(action <= 3)
                        action = 3;
                    /* on augmente la selection de x pixels */
                }
                else if ( opt.getRightKey() )
                {
                    action -= 1;
                    if( action == 0)
                        action = 0;
                    /* on diminue la selection de x pixels */
                }
                else if ( opt.getDownKey() )
                {
                    action -= 1;
                    if( action == 0)
                        action = 0;
                    /* on augmente la selection de x pixels */
                }
                else if ( opt.getValidKey() )
                {
                    quitter = true;
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


bool loadImage()
{
    /* image fond */
    Image imageFond;
    Sprite spriteFond;
    /*if(imageFond.LoadFromFile("image.jpg"))
    {
    	spriteFond.SetImage(imageFond);
    }*/


    /* 4 modes de jeu */
    Font fontFond;
    String text[4];
    /*if(fontFond.LoadFromFile("Arial.ttf"))
    {
    	text[0].SetText("Créer une partie");
    	text[1].SetText("Joindre une partie");
    	text[2].SetText("Options");
    	text[3].SetText("Quitter");
    	for(int i = 0 ; i < 4 ; i++)
    	{
    		text[i].SetFont(fontFond);
    		text[i].SetSize(20);
    		text.SetPosition(vector2f(50, i*50));
    	}
    }*/
}
