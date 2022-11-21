/*
* Main file, contains the game loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Game.h"
#include "./include/Map.h"

#define MAP_SIZE 10

#define false 0
#define true 1

/*
* Main function, contains the game loop.
*/
int main(void)
{
    int gameIsFinished = false;

    int** map = generateMap(MAP_SIZE);
    generateBonusMalus(map,MAP_SIZE);

    while(!gameIsFinished)
    {
        showMap(map, MAP_SIZE);
        gameIsFinished = handlePlayerInput(getPlayerInput());
    }

    clearScreen();
    printf("Thanks for playing!\n");

    return EXIT_SUCCESS;
}