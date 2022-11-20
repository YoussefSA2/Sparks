#ifndef _PLAYER_H
#define _PLAYER_H

#include "./Constants.h"
#include "./Coordinates.h"

typedef struct Player Player;
struct Player{
    float energy;
    Coordinates position;
    int nbRewinds;
};

Player initPlayer();

char move(Player* player, char direction);
void modifyEnergy(Player* player, int value);

#endif