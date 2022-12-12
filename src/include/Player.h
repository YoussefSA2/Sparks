#ifndef _PLAYER_H
#define _PLAYER_H

#include "./Constants.h"
#include "./Coordinates.h"
#include "./cvector.h"

typedef struct Player Player;
struct Player{
    float energy;
    Coordinates position;
    int nbRewinds;
    cvector_vector_type(Coordinates) movesHistory;
};

Player initPlayer();

char move(Player* player, char direction);
void modifyEnergy(Player* player, int value);
int savePlayer(Player* player, char* saveFileName);
int loadPlayer(Player* player, char* saveFileName);

#endif