#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "action.h"
#include <iostream>
#include <string>
#include <fstream>

//include C
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // struct dirent, opendir(), readdir(), closedir()
#include <sys/types.h> // DIR type 

using namespace sf;

int create ( sf::RenderWindow& window, myOption& opt, sf::SocketTCP& sck ) 
{	
	int nbMap = 0;
	
	//lecture d'un repertoire
	std::ofstream repertoire( "maps/mesmaps", std::ios::out | std::ios::trunc );
	DIR * dir;
	struct dirent * entry;
	dir = opendir("maps/" );
 
	while((entry = readdir(dir)) != NULL)
		repertoire << entry->d_name << std::endl;
	closedir(dir);
	repertoire.close();
	//Fin lecture
	
	//ecriture dans un string du contenu du repertoire en supprimant tous ce qui n'est pas un extension de map.
	std::ifstream listMaps( "maps/mesmaps", std::ios::in );
	std::string maMap;
	std::string mesMaps;
	if(listMaps)
	{
		while (!listMaps.eof())
		{
			listMaps >> maMap;
			if( maMap.length() > 7 && !listMaps.eof() && maMap.substr(maMap.length()-7,7) == ".pacmap")
			{
				mesMaps += maMap + '\n'; 
				nbMap ++ ;	
			}
		}
		listMaps.close();
	}
	//fin ecriture
	
	
    bool quitter = false ;
    int action = 1 ;
    unsigned char focus = 1 ; 
    char nbPlayers = 51 ; //code ascii de 3
	int cptMap = 0 ;   //compte le nombre de map actuel
    int i = 0 ;  // compte les caractères des maps 1 par 1
    int j = 0 ;   // permet de compter les caractéres pour chaque maps
    
	
	String
		s_players = String ( "Joueurs :" ),
		s_map = String ( "Carte :" ),
		s_valid = String ( "Valider" ),
		s_back = String ( "Retour" ) ,
		s_choseMap = String ( "Ma map" ),
		s_nbPlayers = String ( "3" );
	
	s_players.SetPosition ( 70, window.GetHeight ( ) - 240 ) ;
	s_map.SetPosition ( 70, window.GetHeight ( ) - 200 ) ;
	s_valid.SetPosition ( 70, window.GetHeight ( ) - 140 ) ;
	s_back.SetPosition ( 70, window.GetHeight ( ) - 100 ) ;
	s_choseMap.SetPosition ( 200, window.GetHeight ( ) -200 ) ;
	s_nbPlayers.SetPosition ( 200, window.GetHeight ( ) - 240 ) ;
	
	
	
	std::size_t pos =0;
	std::vector<std::string> listMap;

	while(j<nbMap)
	{			
		j++;
		i=0;			
		while(mesMaps[i+static_cast<int>(pos)] != '\n' && mesMaps[i] != '\0' )
			i++;
		if(mesMaps[pos] != '\0') // evite l'erreur de fin de fichier
		{

			listMap.push_back(mesMaps.substr(pos,i));
			s_choseMap.SetText(listMap[cptMap]);
			pos += i+1;
		}
	}
	
    while ( ! quitter ) // Boucle d'affichage
    {
		
		window.Clear ( ) ;
		
		s_players.SetColor ( Color ( 255, 255, 255, ( focus == 1 ) ? 255 : 150 ) ) ;
		s_map.SetColor ( Color ( 255, 255, 255, ( focus == 2 ) ? 255 : 150 ) ) ;
		s_valid.SetColor ( Color ( 255, 255, 255, ( focus == 3 ) ? 255 : 150 ) ) ;
		s_back.SetColor ( Color ( 255, 255, 255, ( focus == 4 ) ? 255 : 150 ) ) ;
		s_choseMap.SetColor( Color ( 255, 255, 255, ( focus == 2 ) ? 255 : 150 ) ) ;
		s_nbPlayers.SetColor ( Color ( 255, 255, 255, ( focus == 1 ) ? 255 : 150 ) ) ;
		
		s_valid.SetX ( ( focus == 3 ) ? 90 : 70 ) ;
		s_back.SetX ( ( focus == 4 ) ? 90 : 70 ) ;
		
		window.Draw ( s_players ) ;
		window.Draw ( s_map ) ;
		window.Draw ( s_valid ) ;
		window.Draw ( s_back ) ;
		window.Draw ( s_choseMap ) ;
		window.Draw( s_nbPlayers ) ;
		
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
				if ( event.Key.Code == opt.getUpKey() ) // Appui sur la touche Haut
				{
					if ( focus == 1 )
						focus = 4 ;
					else
						focus -- ;

				}
				else if ( event.Key.Code == opt.getDownKey() ) // Appui sur la touche Bas
				{
					if ( focus == 4 )
						focus = 1 ;
					else
						focus ++ ;
				}
				else if ( event.Key.Code == opt.getLeftKey() ) // Appui sur la touche Gauche
				{
					if ( focus == 1 )
					{
						if( nbPlayers > 50 )  // code ascii de 2
							nbPlayers -- ;
						std::string tmp;
						tmp += nbPlayers; 
						
						s_nbPlayers.SetText( tmp ) ;
					}
					else if ( focus == 2 )
					{
						action = 0 ;
						cptMap++;
						if(cptMap >= nbMap)
							cptMap = 0 ;
						s_choseMap.SetText(listMap[cptMap]);
					}
					else
						action ++ ;
				}
				else if ( event.Key.Code == opt.getRightKey() ) // Appui sur la touche Bas
				{
					if ( focus == 1 )
					{
						if( nbPlayers < 52 )  // code ascii de 4
							nbPlayers ++ ;
						std::string tmp;
						tmp += nbPlayers; 
						
						s_nbPlayers.SetText( tmp ) ;
					}
					else if ( focus == 2 )
					{
						action = 0 ;
						cptMap--;
						if(cptMap < 0)
							cptMap = nbMap-1 ;
						s_choseMap.SetText(listMap[cptMap]);
					}
					else
						action -- ;
				}
				else if ( event.Key.Code == opt.getValidKey() ) // Appui sur la touche Valider
				{
					quitter = true ;
					if ( focus == 4 )
						action = 1 ;
					else
					{
						action = 5 ;
						// connection
						pid_t pid = fork();
						if ( pid == 0 )
						{
							std::string strNbPlayers ;
							strNbPlayers = static_cast<char>(nbPlayers) ;
							std::cout<<"maps/" + listMap[cptMap]<<std::endl;
							
							execl("./Pacman_Serv", "./Pacman_Serv", strNbPlayers.c_str ( ), "maps/default.pacmap"  ,NULL);
						}
						else
						{
							sleep(3.f);
							quitter = true ;
							if (sck.Connect(8910, "127.0.0.1") == Socket::Done)
							{
								Sleep ( 0.050f ) ;
									
									char* c = new char[2] ;
									std::size_t r ;
									
									sck.Receive ( c, static_cast < std::size_t > ( sizeof ( char ) * 2 ), r ) ;
									
									if ( c[0] == '0' )
									{
										quitter = true;
										action = 1 ;
									}
									else
									{
										quitter = true;
										action = 5;
									}
							}
						}
					}
				}
			break;
			
			default :
			break;
			
			} // Switch des évènements
			
		} // Boucle des évènements
		
	} // Boucle d'affichage
	
	return action;
	
}
