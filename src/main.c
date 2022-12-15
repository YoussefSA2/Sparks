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
    showMenu();
    
    int gameIsFinished = false;

    int** map = generateMap(MAP_SIZE);
    Player player = initPlayer();
    
    do{} while (launchGame(getPlayerInput(), &player, map) == INVALID_LAUNCH_GAME_CHOICE);
    
    showMap(map, MAP_SIZE, player);
  
    while(!gameIsFinished)
    {   
        if (kbhit()) {
            int lastPlayerAction = handlePlayerInput(getPlayerInput(), &player, map);
            clearScreen();
            showMap(map, MAP_SIZE, player);
            printLastAction(lastPlayerAction);
            displayAvailableCommands();
            gameIsFinished = checkGameState(player, lastPlayerAction, map);
        }
        
    }

    printf("Thanks for playing!\n");
    freeMap(map, MAP_SIZE);

    return EXIT_SUCCESS;
}