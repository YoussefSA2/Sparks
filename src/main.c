/*
* Main file, contains the game loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "./include/Game.h"
#include "./include/Map.h"
#include "./include/Player.h"

#define MAP_SIZE 10

/*
* Main function, contains the game loop.
*/
int main(void)
{
    int gameState = GAME_IS_RUNNING;

    int** map = generateMap(MAP_SIZE);
    Player player = initPlayer();

    showMap(map, MAP_SIZE);
  
    while(gameState != GAME_IS_FINISHED)
    {   
        if(kbhit()){
            gameState = handlePlayerInput(getch(), &player);
            clearScreen();
            showMap(map, MAP_SIZE);
            printLastAction(gameState);
        }
    }

    clearScreen();
    printLastAction(gameState);
    printf("Thanks for playing!\n");

    return EXIT_SUCCESS;
}