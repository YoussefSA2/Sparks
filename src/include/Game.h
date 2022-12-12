#ifndef _GAME_H
#define _GAME_H

#include "./Constants.h"
#include "./Player.h"
#include "./Map.h"
#include <conio.h>


int saveGame();
void clearScreen();
char getPlayerInput();
int handlePlayerInput(char input, Player* player, int** map);
void printLastAction(char gameState);
int checkGameState(Player player, int lastPlayerAction);
int killPlayer();
int handlePlayerVictory();
void displayAvailableCommands();

#endif