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

int savePlayer(Player* player, char* saveFileName){
    FILE* file = fopen(saveFileName, "wb");
    if (file == NULL) {
        printf("Fichier non trouvé.");
        return EXIT_FAILURE;
    }
    
    // save all informations one by one 
    // because saving the entire Player structure doesn't work
    fwrite(&(player->energy), sizeof(float), 1, file);
    fwrite(&(player->nbRewinds), sizeof(int), 1, file);
    fwrite(&(player->position), sizeof(Coordinates), 1, file);
    
    // saving number of moves contained in player history
    // because we need it to load it after
    unsigned int nbMoves = cvector_size(player->movesHistory);
    fwrite(&nbMoves, sizeof(unsigned int), 1, file);
    fwrite(player->movesHistory, sizeof(Coordinates), nbMoves, file);

    return fclose(file);

}

int loadPlayer(Player* player, char* saveFileName){
    FILE* file = fopen(saveFileName, "rb");
    if (file == NULL) {
        printf("Fichier non trouvé.");
        return EXIT_FAILURE;
    }

    float loadEnergy;
    int loadNbRewinds;
    Coordinates loadPosition;
    cvector_vector_type(Coordinates) loadMovesHistory = NULL;

    // loading infos one by one
    fread(&loadEnergy, sizeof(float), 1, file);
    fread(&loadNbRewinds, sizeof(int), 1, file);
    fread(&loadPosition, sizeof(Coordinates), 1, file);
    
    unsigned int nbMovesToLoad;
    fread(&nbMovesToLoad, sizeof(unsigned int), 1, file);
    
    Coordinates loadMove;
    for (unsigned int i = 0; i < nbMovesToLoad; i++){
        fread(&loadMove, sizeof(Coordinates), 1, file);
        cvector_push_back(loadMovesHistory, loadMove);
    }
    
    // modify the player with loaded infos
    player->energy = loadEnergy;
    player->nbRewinds = loadNbRewinds;
    player->position = loadPosition;
    player->movesHistory = loadMovesHistory;

    return fclose(file);

}