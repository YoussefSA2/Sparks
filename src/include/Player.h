#ifndef _PLAYER_H
#define _PLAYER_H

#include "./Coordinates.h"

#define GAME_IS_RUNNING 0

#define MOVE_NORTH_INPUT '8'
#define MOVE_NORTH_EAST_INPUT '9'
#define MOVE_EAST_INPUT '6'
#define MOVE_SOUTH_EAST_INPUT '3'
#define MOVE_SOUTH_INPUT '2'
#define MOVE_SOUTH_WEST_INPUT '1'
#define MOVE_WEST_INPUT '4'
#define MOVE_NORTH_WEST_INPUT '7'

typedef struct Player Player;
struct Player{
    float energy;
    Coordinates position;
    int nbRewinds;
};

Player initPlayer();

void move(Player* player, int direction);
void modifyEnergy(Player* player, int value);
#endif