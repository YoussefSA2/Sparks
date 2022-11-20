/*
* Main file, contains the game loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Game.h"
#include "./include/Map.h"
#include "./include/Player.h"

/*
* Main function, contains the game loop.
*/
int main(void)
{
    int gameState = GAME_IS_RUNNING;

    int** map = generateMap(MAP_SIZE);
    Player player = initPlayer();

    showMap(map, MAP_SIZE, player);

  
    while(gameState != GAME_IS_FINISHED)
    {   
        gameState = handlePlayerInput(getPlayerInput(), &player, map);
        clearScreen();
        showMap(map, MAP_SIZE, player);
        printLastAction(gameState);
    }

    clearScreen();
    printLastAction(gameState);
    printf("Thanks for playing!\n");

    return EXIT_SUCCESS;
}