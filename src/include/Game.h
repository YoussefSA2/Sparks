/**
 * @file Game.h
 * @brief Functions prototypes to handle the game.
 * @authors Sithursha Sivathevan, Marwa Tourabi, Charles-Meldhine Madi Mnemoi
*/

#ifndef _GAME_H
#define _GAME_H

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./console.h"
#include "./Constants.h"
#include "./Display.h"
#include "./Map.h"
#include "./Menus.h"
#include "./Path.h"
#include "./Player.h"
#include "./Save.h"

int handlePlayerInput(char input, Player* player, int** map);
void printLastAction(char gameState, Player player);
int checkGameState(Player player, int lastPlayerAction, int** map);
int killPlayer();
int handlePlayerVictory(Player player, int** map);
void displayAvailableCommands();
int launchGame(char playerInput, Player* player, int*** mapPointer);

#endif