/**
 * @file Player.h
 * @brief Functions prototypes to handle the player.
 * @authors
 * @file Coordinates.h
 * @brief Coordinates structure and functions prototypes.
 * @authors Sitursha Sivathevan, Charles-Meldhine Madi Mnemoi
*/
#ifndef _PLAYER_H
#define _PLAYER_H

#include "./Constants.h"
#include "./Coordinates.h"
#include "./cvector.h"

typedef struct Player Player;
struct Player{
    float energy;
    float gainedEnergy;
    float lostEnergy;
    Coordinates position;
    int nbRewinds;
    cvector_vector_type(Coordinates) movesHistory;
};

int alreadyPassedOn(Player* player);
int cancelMove(Player* player);
Player initPlayer(int** map);
int isPlayerInTheMap(Player* player, int mapSize);
void loadPlayer(Player* player, FILE* saveFile);
void modifyEnergy(Player* player, int value);
char move(Player* player, char direction);
void savePlayer(Player* player, FILE* saveFile);
void showPlayerEnergy(Player player);
void showPlayerPosition(Player player);

#endif