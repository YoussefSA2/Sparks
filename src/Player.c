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
    player.movesHistory = NULL;
    
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

/**
 * @brief Function which saves the player in a file. It is used in the saveGame() function
 * @param player The player to save.
 * @param saveFileName The name of the file where the player will be saved.
 * XIT_SUCCESS if the player has been saved, EXIT_FAILURE otherwise.
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
 * @param saveFileName The name of the file where the player will be loaded.
 * XIT_SUCCESS if the player has been loaded, EXIT_FAILURE otherwise.
*/
void loadPlayer(Player* player, FILE* saveFile){
    // find the beginning of player infos : they are written after the map
    // so MAP_SIZE * MAP_SIZE * sizeof(int) bytes after the beginning of the file
    fseek(saveFile, MAP_SIZE * MAP_SIZE * sizeof(int), SEEK_SET);

    float loadEnergy;
    int loadNbRewinds;
    Coordinates loadPosition;
    cvector_vector_type(Coordinates) loadMovesHistory = NULL;

    // loading infos one by one
    fread(&loadEnergy, sizeof(float), 1, saveFile);
    fread(&loadNbRewinds, sizeof(int), 1, saveFile);
    fread(&loadPosition, sizeof(Coordinates), 1, saveFile);
    
    unsigned int nbMovesToLoad;
    fread(&nbMovesToLoad, sizeof(unsigned int), 1, saveFile);
    
    Coordinates loadMove;
    for (unsigned int i = 0; i < nbMovesToLoad; i++){
        fread(&loadMove, sizeof(Coordinates), 1, saveFile);
        cvector_push_back(loadMovesHistory, loadMove);
    }
    
    // modify the player with loaded infos
    player->energy = loadEnergy;
    player->nbRewinds = loadNbRewinds;
    player->position = loadPosition;
    player->movesHistory = loadMovesHistory;

}