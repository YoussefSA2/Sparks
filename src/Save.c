/**
 * @file Save.c
 * @brief File containing the functions to handle the save and load of the game.
 * @author Charles-Meldhine Madi Mnemoi
*/

#include "./include/Save.h"

/**
 * @brief Show a menu allowing the player to choose a save slot.
 * @return The save slot chosen by the player.
*/
char chooseSaveSlot()
{
    char saveSlot;
    int saveSlotIsValid = false;

    while (!saveSlotIsValid)
    {
        printf("Choose a save slot to save/load the game (1-3): ");
        saveSlot = getPlayerInput();

        if (saveSlot == '1' || saveSlot == '2' || saveSlot == '3')
        {
            saveSlotIsValid = true;
        }
        else
        {
            printf("Invalid save slot, please try again.\n");
        }
    }

    printf("Save slot %c chosen.\n", saveSlot);

    return saveSlot;
}

/**
 * @brief Function which loads the game from the "save{saveSlot}.sav" file.
 * @param player The player to load
 * @param map The map to load
 * @param saveSlot The save slot number where the game is saved.
 * @return GAME_LOAD_SUCCESS if the game is loaded, GAME_LOAD_FAILED if an error occured.
*/
int loadGame(Player* player, int** map, char saveSlot)
{
    char saveFileName[12];
    sprintf(saveFileName, "save%c.sav", saveSlot);
    
    FILE* saveFile = fopen(saveFileName, "rb");
    if (saveFile == NULL) {
        printf("Error while opening the save file, impossible to load the game. Launching a new one.\n");
        return GAME_LOAD_FAILED;
    }
    
    loadMap(map, saveFile);
    loadPlayer(player, saveFile);

    fclose(saveFile);

    return GAME_LOAD_SUCCESS;
}

/**
* @brief Function which saves the game to the "save{saveSlot}.sav" file.
* It calls the saveMap and savePlayer functions.
* @param player The player.
* @param map The map.
* @param saveFileSlot The save slot number where the game is saved.
* @return PLAYER_SAVED if the game is saved, EXIT_FAILURE if an error occured.
*/
int saveGame(Player* player, int** map, char saveSlot) {
    
    char saveFileName[12];
    sprintf(saveFileName, "save%c.sav", saveSlot);
    
    FILE* saveFile = fopen(saveFileName, "wb");
    if (saveFile == NULL) {
        printf("Error while creating the save file, impossible to save the game. Exiting.");
        exit(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    saveMap(map, saveFile);
    fclose(saveFile);

    saveFile = fopen(saveFileName, "ab");
    if (saveFile == NULL) {
        printf("Error while creating the save file, impossible to save the game. Exiting.");
        exit(EXIT_FAILURE);
        return EXIT_FAILURE;
    }
    savePlayer(player, saveFile);
    fclose(saveFile);

    return PLAYER_SAVED;
}

/** 
 * @brief Function which saves the map in a file. It is used in the saveGame function.
 * @param map The map to save.
 * @param saveFileName The name of the file to save the map in.
*/
void saveMap(int** map, FILE* saveFile)
{
    // create a static map because you can't save a dynamic one
    int mapToSave[MAP_SIZE][MAP_SIZE];

    for (unsigned int i = 0; i < MAP_SIZE; i++)
    {
        for(unsigned int j = 0; j < MAP_SIZE; j++)
        {
            mapToSave[i][j] = map[i][j];
        }
    }

    fwrite(mapToSave, sizeof(int), MAP_SIZE * MAP_SIZE, saveFile);
}

/** 
 * @brief Function which loads the map from a file. It is used in the loadGame function.
 * @param map The map to load.
 * @param saveFileName The name of the file to load the map from.
*/
void loadMap(int** map, FILE* saveFile)
{
    // load a static map
    int loadMap[MAP_SIZE][MAP_SIZE];
    fread(loadMap, sizeof(int), MAP_SIZE * MAP_SIZE, saveFile);

    // free the map and allocate a new one
    freeMap(map, MAP_SIZE);
    map = malloc(MAP_SIZE * sizeof(int*));
    for (unsigned int i = 0; i < MAP_SIZE; ++i){
        map[i] = malloc(MAP_SIZE * sizeof(int));
    }

    // fill the dynamic map with the load data
    for (unsigned int i = 0; i < MAP_SIZE; i++)
    {
        for(unsigned int j = 0; j < MAP_SIZE; j++)
        {
            map[i][j] = loadMap[i][j];
        }
    }

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

