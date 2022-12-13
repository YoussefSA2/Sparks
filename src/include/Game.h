#ifndef _GAME_H
#define _GAME_H

#include "./Constants.h"
#include "./Player.h"
#include "./Map.h"

int saveGame(Player* player, int** map);
void clearScreen();
char getPlayerInput();
int handlePlayerInput(char input, Player* player, int** map);
void printLastAction(char gameState);
int checkGameState(Player player, int lastPlayerAction, int** map);
int killPlayer();
int handlePlayerVictory();
void displayAvailableCommands();
void loadGame(Player* player, int** map, char* playerSaveFile, char* mapSaveFile);
void showMenu();
void choiceMenu(char playerInput, Player* player, int** map, char* playerSaveFile, char* mapSaveFile);

#endif