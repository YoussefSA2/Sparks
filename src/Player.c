/**
 * @file Player.c
 * @brief File which handles the Player structure and functions.
 * @authors Youssef Saidi, Sitursha Sivathevan, Charles-Meldhine Madi Mnemoi
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Player.h"

/**
 * @brief Initializes the player.
 * @param map The map on which the player will play.
 * @return The initialized player.
 * 
 * @details This function initializes the player, and returns it.
*/
Player initPlayer(int** map){
    
    Player player;
    Coordinates startPosition = {0, 0};
    
    player.position.x = 0;
    player.position.y = 0;
    player.position.content = map[player.position.y][player.position.x];
    player.energy = 100;
    player.gainedEnergy = 0;
    player.lostEnergy = 0;
    player.nbRewinds = 6;
    player.movesHistory = NULL;
    cvector_push_back(player.movesHistory, startPosition);

    
    return player;
}

/**
 * @brief Function which moves the player.
 * It only changes the player position (the display will be handled in the showMap() function from Map.c).
 * It returns the direction input given by the user (see the Player.h file for the constants).
 * @param player The player.
 * @param direction The direction in which the player wants to move.
 * @return The direction input given by the user.
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

/**
 * @brief Function which cancels the last move of the player.
 * @param player The player.
 * @return NO_REWINDS_LEFT if the player has no more rewinds left, CANCEL_MOVE_SUCCESS otherwise.
*/
int cancelMove(Player* player){
    
    if(player->nbRewinds <= 0){
        return NO_REWINDS_LEFT;
    }

    /*
    * If the player has only one move in his history, it means that he hasn't moved yet
    * and therefore there is no move to cancel.
    */
    if (cvector_size(player->movesHistory) <= 1){
        return NO_MOVE_TO_CANCEL;
    }

    // we want to go back to the second to last position
    Coordinates secondToLastPosition = player->movesHistory[cvector_size(player->movesHistory)-2];
    
    // revert coordinates because the map is displayed in a different way than the player moves
    
    Coordinates positionOnTheMap = {secondToLastPosition.y, secondToLastPosition.x};

    player->position = positionOnTheMap;
    
    // remove the last move from the history as it has been cancelled
    cvector_pop_back(player->movesHistory); 

    player->nbRewinds--;

    return CANCEL_MOVE_SUCCESS;
}

/**
 * @brief Function which modifies the player energy.
 * @param player The player.
 * @param value The value to add to the player energy.
 * 
 * @details This function modifies the player energy, and returns it.
 * It also updates the gainedEnergy and lostEnergy attributes of the player.
*/
void modifyEnergy(Player* player, int value){
    if (value>0){
        player->gainedEnergy += value;
    }
    else if (value<0){
        player->lostEnergy += value;
    }

    player->energy += value;
}

/**
 * @brief Function which checks if the player already passed on a given position, 
 * using the player moves history and player's current position.
 * @param player The player.
 * @return true if the player already passed on the given position, false otherwise.
*/
int alreadyPassedOn(Player* player){
    unsigned int nbMoves = cvector_size(player->movesHistory);
    for (unsigned int i = 0; i < nbMoves - 1; i++){
       Coordinates move = {player->movesHistory[i].y, player->movesHistory[i].x};
         if (areEqual(move, player->position)){
              return true;
         }
    }
    return false;
}

/**
 * @brief Function which saves the player in a file. It is used in the saveGame() function
 * @param player The player to save.
 * @param saveFile The file where the player will be saved.
*/
void savePlayer(Player* player, FILE* saveFile){
    // save all informations one by one 
    // because saving the entire Player structure doesn't work
    fwrite(&(player->energy), sizeof(float), 1, saveFile);
    fwrite(&(player->nbRewinds), sizeof(int), 1, saveFile);
    fwrite(&(player->position), sizeof(Coordinates), 1, saveFile);
    
    // saving number of moves contained in player history
    // because we need it to load it after
    unsigned int nbMoves = cvector_size(player->movesHistory);
    fwrite(&nbMoves, sizeof(unsigned int), 1, saveFile);
    fwrite(player->movesHistory, sizeof(Coordinates), nbMoves, saveFile);

}

/**
 * @brief Function which loads the player from a file. It is used in the loadGame() function
 * @param player The player to load.
 * @param saveFile The file where the player will be loaded.
*/
void loadPlayer(Player* player, FILE* saveFile){
    // loading infos one by one
    fread(&(player->energy), sizeof(float), 1, saveFile);
    fread(&(player->nbRewinds), sizeof(int), 1, saveFile);
    fread(&(player->position), sizeof(Coordinates), 1, saveFile);
    
    // load all moves in player history
    unsigned int nbMovesToLoad;
    fread(&nbMovesToLoad, sizeof(unsigned int), 1, saveFile);
    
    player->movesHistory = NULL;
    Coordinates move;
    for (unsigned int i = 0; i < nbMovesToLoad; i++){
        fread(&move, sizeof(Coordinates), 1, saveFile);
        cvector_push_back(player->movesHistory, move);
    }    
}

/**
 * @brief Function which displays player energy.
 * @param player The player.
*/
void showPlayerEnergy(Player player){
    printf(" Energy : %f \n", player.energy);
}

/**
 * @brief Function which displays player position.
 * @param player The player.
*/
void showPlayerPosition(Player player){
    printf(" Position : ");
    showCoordinates(player.position);
    printf("\n");
}