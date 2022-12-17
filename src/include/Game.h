#ifndef _GAME_H
#define _GAME_H

#include "./Constants.h"
#include "./Player.h"
#include "./Map.h"
#include <conio.h>


int saveGame(Player* player, int** map);
void clearScreen();
char getPlayerInput();
int handlePlayerInput(char input, Player* player, int** map);
void printLastAction(char gameState, Player player);
int checkGameState(Player player, int lastPlayerAction, int** map);
int killPlayer();
int handlePlayerVictory();
void displayAvailableCommands();
int loadGame(Player* player, int** map);
void showMenu();
int launchGame(char playerInput, Player* player, int** map);

#endif