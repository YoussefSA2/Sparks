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

Player initPlayer();

char move(Player* player, char direction);
void modifyEnergy(Player* player, int value);
void savePlayer(Player* player, FILE* saveFile);
void loadPlayer(Player* player, FILE* saveFile);

#endif