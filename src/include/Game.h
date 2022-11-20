#ifndef _GAME_H
#define _GAME_H

#include "./Player.h"

/*
* Game states
*/
#define GAME_IS_FINISHED 99
#define GAME_IS_RUNNING 0

/*
* Player inputs
*/

#define EXIT_INPUT 'q'
// Direction inputs
#define MOVE_NORTH_INPUT '8'
#define MOVE_NORTH_EAST_INPUT '9'
#define MOVE_EAST_INPUT '6'
#define MOVE_SOUTH_EAST_INPUT '3'
#define MOVE_SOUTH_INPUT '2'
#define MOVE_SOUTH_WEST_INPUT '1'
#define MOVE_WEST_INPUT '4'
#define MOVE_NORTH_WEST_INPUT '7'

int saveGame();
void clearScreen();
char getPlayerInput();
int handlePlayerInput(char input, Player* player);
void printLastAction(char gameState);

#endif