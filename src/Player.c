/**
* File which handles the Player structure and functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Player.h"
#define INIT_ENERGY 100

Player initPlayer(){
    Player player;// Je créer un nouveau player et je lui initialise ces valeurs
    player.position[0]=0;// Quand la struct coord seras pretes il faudras remplacé
    player.position[1]=0;
    player.energy=INIT_ENERGY;
    player.nbRewinds=20;
    printf("Player initialised\n");
    return player;
}
void move(Player* player, int direction){
    switch(direction){
        case 1://A faire quand les fonction de map seront prets
            printf("UP\n");
            break;
        case 2:
            printf("DOWN\n");
            break;
        case 3:
            printf("LEFT\n");
            break;
        case 4:
            printf("RIGHT\n");
            break;
    }
}
void modifyEnergy(Player* player, int value){
    player->energy=value;
}
