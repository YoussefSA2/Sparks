#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./Constants.h"
#include "./Map.h"
#include "./Path.h"
#include "./Player.h"
#include "./utils.h"
#include "./Save.h"

int saveGame(Player* player, int** map, char saveSlot);
void clearScreen();
char getPlayerInput();
int handlePlayerInput(char input, Player* player, int** map);
void printLastAction(char gameState, Player player);
int checkGameState(Player player, int lastPlayerAction, int** map);
int killPlayer();
int handlePlayerVictory(Player player, int** map);
void displayAvailableCommands();
int loadGame(Player* player, int** map, char saveSlot);
void mainMenu();
int launchGame(char playerInput, Player* player, int*** mapPointer);

#endif