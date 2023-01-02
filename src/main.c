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
    int gameIsFinished = false;

    int** map = generateMap(MAP_SIZE);
    Player player = initPlayer(map);

    mainMenu();
    int launchGameResult = launchGame(getPlayerInput(), &player, map);
    while (launchGameResult == INVALID_LAUNCH_GAME_CHOICE || launchGameResult == END_REPLAY)
    {
        mainMenu();
        launchGameResult = launchGame(getPlayerInput(), &player, map);
    }
    
    showMap(map, MAP_SIZE, player);
  
    while(!gameIsFinished)
    {   
        if (kbhit()) {
            int lastPlayerAction = handlePlayerInput(getPlayerInput(), &player, map);
            clearScreen();
            showMap(map, MAP_SIZE, player);
            printLastAction(lastPlayerAction, player);
            displayAvailableCommands();
            gameIsFinished = checkGameState(player, lastPlayerAction, map);
        }
        
    }

    printf("\nThanks for playing!\n");
    freeMap(map, MAP_SIZE);

    return EXIT_SUCCESS;
}