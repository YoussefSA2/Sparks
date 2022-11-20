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
* Fonction which checks if the player is still on the map after moving. 
*/
int isPlayerInTheMap(Player* player, int mapSize) {
    if (player->position.x < 0 || player->position.x >= mapSize || player->position.y < 0 || player->position.y >= mapSize) {
        return false;
    }
    return true;
}

/*
* Fonction which handles player movement.
* It checks if the player is still on the map after moving
* and change player energy given the destination square (tree, food, obstacle).
*/
char handlePlayerMove(Player* player, char direction) {
    move(player, direction);
    if (!isPlayerInTheMap(player, MAP_SIZE)) {
        move(player, getOppositeDirection(direction)); // TODO : in the future, use moveHistory to go back to the previous position.
        return INVALID_DIRECTION_INPUT;
    }

    // TODO : change player energy given the destination square (tree, food, obstacle).

    return direction;
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
            return handlePlayerMove(player, input);
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
        case INVALID_DIRECTION_INPUT:
            printf("You can't go there!\n");
            break;
        default:
            printf("Invalid input.\n");
            break;
    }
}



