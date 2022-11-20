/*
* Main file, contains the game loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Game.h"
#include "./include/Map.h"
#include "./include/Player.h"
#include <conio.h>
#define MAP_SIZE 10

#define false 0
#define true 1


/*
* Main function, contains the game loop.
*/
int main(void)
{
    int gameIsFinished = false;
    char k;
    int** map = generateMap(MAP_SIZE);
    Player player = initPlayer();
    move(&player,1);
    move(&player,2);
    showMap(map, MAP_SIZE);//on attendant d'avoir un truc prets pas besoin de reload la map a chaque fois
    while(!gameIsFinished)
    {
        if(kbhit()){//Check if a key is pressed
            k = getch();//Get the key that is pressed
            switch(k){//Pour depanner j'ai fait ca mais faut trouver autre chose pour pas trops chargé le main
                case 'Z':
                case 'z':
                    move(&player,1);
                    break;
                case 'S':
                case 's':
                    move(&player,2);
                    break;
                case 'Q':    
                case 'q':
                    move(&player,3);
                    break; 
                case 'D':    
                case 'd':
                    move(&player,4);
                    break;
               
            }       
        }
        
        //gameIsFinished = handlePlayerInput(getPlayerInput());
    }

    clearScreen();
    printf("Thanks for playing!\n");

    return EXIT_SUCCESS;
}