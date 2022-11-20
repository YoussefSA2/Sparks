/**
* File which handles the Player structure and functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Player.h"
#define INIT_ENERGY 100

/*
* Function which initializes the player.
*
*/
Player initPlayer(){
    
    Player player;
    
    player.position.x = 0;
    player.position.y = 0;
    player.energy = 100;
    player.nbRewinds = 6;
    
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
