/**
* File which handles the Player structure and functions.
*/
#include <stdio.h>
#include <stdlib.h>
#include "./include/Player.h"

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

/*
* Function which moves the player.
* It only changes the player position (the display will be handled in the showMap() function).
* It returns the direction input given by the user (see the Player.h file for the constants).
*/

char move(Player* player, char direction){
    switch(direction){
        case MOVE_NORTH_INPUT:
            player->position.y--;
            break;
        case MOVE_NORTH_EAST_INPUT:
            player->position.x++;
            player->position.y--;
            break;
        case MOVE_EAST_INPUT:
            player->position.x++;
            break;
        case MOVE_SOUTH_EAST_INPUT:
            player->position.x++;
            player->position.y++;
            break;
        case MOVE_SOUTH_INPUT:
            player->position.y++;
            break;
        case MOVE_SOUTH_WEST_INPUT:
            player->position.x--;
            player->position.y++;
            break;
        case MOVE_WEST_INPUT:
            player->position.x--;
            break;
        case MOVE_NORTH_WEST_INPUT:
            player->position.x--;
            player->position.y--;
            break;
    }

    return direction;
}

/*
* Function which modifies the player energy.
*/
void modifyEnergy(Player* player, int value){
    player->energy += value;
}
