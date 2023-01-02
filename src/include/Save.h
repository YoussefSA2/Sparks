/**
 * @file Save.h
 * @brief Functions prototypes to handle the save and load of the game.
 * @author Charles-Meldhine Madi Mnemoi
*/

#ifndef SAVE_H
#define SAVE_H

#include "./Constants.h"
#include "./Map.h"
#include "./Player.h"
#include "./utils.h"
#include <stdlib.h>
#include <stdio.h>

char chooseSaveSlot();
int loadGame(Player* player, int** map, char saveSlot);
int saveGame(Player* player, int** map, char saveSlot);
void loadMap(int** map, FILE* saveFile);
void saveMap(int** map, FILE* saveFile);
void loadPlayer(Player* player, FILE* saveFile);
void savePlayer(Player* player, FILE* saveFile);

#endif