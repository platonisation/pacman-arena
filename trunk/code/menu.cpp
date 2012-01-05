#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "action.h"

using namespace sf;

//bool loadImage();

int menu ( RenderWindow window, myOption& opt )
{
	
    bool quitter = false ;
    int action = 4 ;
	
    /* Chargement des images necessaires
	
    if(!loadImage())
    {
        //en cas de pépin ( image non dispo )
        return 0;
    }
	
	*/
	
	String
		s_join = String ( "Rejoindre une partie" ),
		s_create = String ( "Créer une partie" ),
		s_option = String ( "Paramètres" ),
		s_quit = String ( "Quitter" ) ;
	
	s_join.SetPosition ( 50, window.GetHeight ( ) - 170 ) ;
	s_create.SetPosition ( 50, window.GetHeight ( ) - 130 ) ;
	s_option.SetPosition ( 50, window.GetHeight ( ) - 90 ) ;
	s_quit.SetPosition ( 50, window.GetHeight ( ) - 50 ) ;
	
	s_join.SetColor ( Color ( 255, 255, 255, 255 ) ) ;
	s_join.SetColor ( Color ( 255, 255, 255, 150 ) ) ;
	s_join.SetColor ( Color ( 255, 255, 255, 150 ) ) ;
	s_join.SetColor ( Color ( 255, 255, 255, 150 ) ) ;
	
    while ( ! quitter ) // Boucle d'affichage
    {
		
		window.Clear ( ) ;
		
		window.Draw ( s_join ) ;
		window.Draw ( s_create ) ;
		window.Draw ( s_option ) ;
		window.Draw ( s_quit ) ;
		
		window.Display ( ) ;
		
        Event event ;
        while ( window.GetEvent ( event ) ) // Boucle des évènements
        {
			
			switch ( event.Type ) // Type de l'évènement en attente :
			{
				
			case Event::Closed : // Croix en haut à droite
				action = 0;
				quitter = true;
			break;
			
			case Event::KeyPressed : // Appui sur une touche du clavier
				if ( event.Type.Code == opt.getUpKey() ) // Appui sur la touche Haut
				{
					if ( action == 0 )
						action = 2 ;
					else if ( action == 4 )
						action = 0 ;
					else
						action ++ ;
				}
				else if ( event.Type.Code == opt.getDownKey() ) // Appui sur la touche Bas
				{
					if ( action == 0 )
						action = 4 ;
					else if ( action == 2 )
						action = 0 ;
					else
						action -- ;
				}
				else if ( event.Type.Code == opt.getValidKey() ) // Appui sur la touche Valider
				{
					quitter = true;
				}
			break;
			
			default :
			break;
			
			}
			
		} // Boucle des évenements
		
	} // Boucle d'affichage
	
	return action;
	
}

/*
bool loadImage()
{
    /* image fond
    Image imageFond;
    Sprite spriteFond;
    /*if(imageFond.LoadFromFile("image.jpg"))
    {
    	spriteFond.SetImage(imageFond);
    }*/


    /* 4 modes de jeu */
    /*Font fontFond;
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
    }*//*
}
*/
