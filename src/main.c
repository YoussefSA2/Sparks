/*
* Main file, contains the game loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Game.h"

/*
* Main function, contains the game loop.
*/
int main(void)
{    
    int gameIsFinished = false;

    int** map = generateMap(MAP_SIZE, EASY);
    Player player = initPlayer(map);

    mainMenu();
    int launchGameResult = launchGame(getPlayerInput(), &player, &map);
    while (launchGameResult == INVALID_LAUNCH_GAME_CHOICE || launchGameResult == END_REPLAY)
    {
        mainMenu();
        launchGameResult = launchGame(getPlayerInput(), &player, &map);
    }
    
    showMap(map, MAP_SIZE, player);
  
    while(!gameIsFinished)
    {   
        int lastPlayerAction = handlePlayerInput(getPlayerInput(), &player, map);
        clearScreen();
        showMap(map, MAP_SIZE, player);
        printLastAction(lastPlayerAction, player);
        displayAvailableCommands();
        gameIsFinished = checkGameState(player, lastPlayerAction, map);
    }

    saveGame(&player, map, chooseSaveSlot());
    freeMap(map, MAP_SIZE);
    printf("\nThanks for playing!\n");

    return EXIT_SUCCESS;
}