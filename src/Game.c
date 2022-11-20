/*
* File containing all the functions needed to handle the game in its main loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Game.h"

/*
* Saves the game.
* TODO : save the map, the player position, etc. into a file (JSON? .txt?)
*/
int saveGame() {
    return GAME_IS_FINISHED;
}

/*
* Clears the console.
*/
void clearScreen()
{
    #ifdef _WIN32 // Windows
        system("cls");
    #else // Linux
        system("clear");
    #endif
}

/*
* Returns the player input.
*/
char getPlayerInput() {
    return getchar();
}

/*
* Function which handles all player inputs.
* It calls the functions corresponding to the player input.
* For example, if the player inputs 'q', it will call the saveGame function, etc.
*/
int handlePlayerInput(char input) {
    switch (input) {
        case EXIT_INPUT:
            return saveGame();
        // TODO : add move player, save game, etc.
        default:
            return false;
            break;
    }
}



