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
    #ifdef _WIN32 // Windows
        if (kbhit()) {
            return getch();
        }
    #else // Linux
        char input = getchar();
        getchar(); // To remove the \n character you get when you press enter.
        return input;
    #endif
}

/*
* Function which handles all player inputs.
* It calls the functions corresponding to the player input.
* For example, if the player inputs 'q', it will call the saveGame function, etc.
*/
int handlePlayerInput(char input, Player* player) {
    switch (input) {
        case EXIT_INPUT:
            return saveGame();
        case MOVE_NORTH_INPUT:
        case MOVE_NORTH_EAST_INPUT:
        case MOVE_EAST_INPUT:
        case MOVE_SOUTH_EAST_INPUT:
        case MOVE_SOUTH_INPUT:
        case MOVE_SOUTH_WEST_INPUT:
        case MOVE_WEST_INPUT:
        case MOVE_NORTH_WEST_INPUT:
            return move(player, input); // TODO : call handlePlayerMove() here instead (to check if move is possible, handle collisions, etc.)
            break;
        default:
            return GAME_IS_RUNNING;
            break;
    }
}

/*
* Function which prints the last action the player did.
*/
void printLastAction(char gameState) {
    switch (gameState) {
        case MOVE_NORTH_INPUT:
            printf("You moved north.\n");
            break;
        case MOVE_NORTH_EAST_INPUT:
            printf("You moved north-east.\n");
            break;
        case MOVE_EAST_INPUT:
            printf("You moved east.\n");
            break;
        case MOVE_SOUTH_EAST_INPUT:
            printf("You moved south-east.\n");
            break;
        case MOVE_SOUTH_INPUT:
            printf("You moved south.\n");
            break;
        case MOVE_SOUTH_WEST_INPUT:
            printf("You moved south-west.\n");
            break;
        case MOVE_WEST_INPUT:
            printf("You moved west.\n");
            break;
        case MOVE_NORTH_WEST_INPUT:
            printf("You moved north-west.\n");
            break;
        case GAME_IS_FINISHED:
            printf("You saved the game.\n");
            break;
        default:
            printf("Invalid input.\n");
            break;
    }
}



