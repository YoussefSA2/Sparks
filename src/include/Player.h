#ifndef _PLAYER_H
#define _PLAYER_H

typedef struct Player Player;
struct Player{//Obliger de initialiser la structure ici sinon ne marche pas
    float energy;
    int position[2];// Quand la struct coord seras pretes il faudras remplacé
    int nbRewinds;
};

Player initPlayer();

void move(Player* player, int direction);
void modifyEnergy(Player* player, int value);
#endif