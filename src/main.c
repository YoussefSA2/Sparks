/**
 * @file main.c
 * @brief Main file, contains the main game loop.
 * @authors Sitursha Sivathevan, Youssef Saidi, Charles-Meldhine Madi Mnemoi
 * 
 * @details This file contains the main function, which runs the main game loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Game.h"

/**
 * @brief Main function, contains the game loop.
 * @return EXIT_SUCCESS if the game ends successfully.
 * 
 * @details This function contains the main game loop, which runs until the game is finished.
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
        if (kbhit()) {
            int lastPlayerAction = handlePlayerInput(getPlayerInput(), &player, map);
            clearScreen();
            showMap(map, MAP_SIZE, player);
            printLastAction(lastPlayerAction, player);
            displayAvailableCommands();
            gameIsFinished = checkGameState(player, lastPlayerAction, map);
        }
        
    }

    saveGame(&player, map, chooseSaveSlot());
    freeMap(map, MAP_SIZE);
    printf("\nThanks for playing!\n");

    return EXIT_SUCCESS;
}