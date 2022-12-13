/**
* File which handles the Map structure and functions.
*/

#include "./include/Map.h"

/*
* Generates a mapSize x mapSize map.
*/
int **generateMap(int mapSize){
    int** map = NULL;

    map=malloc(mapSize * sizeof(int*));

    for (int i=0; i< mapSize; i++)
    {
        map[i]=malloc(mapSize * sizeof(int));
    }
        
    for(int i=0; i<mapSize; i++)
    {
        for(int j=0 ; j<mapSize; j++)
        {
            map[i][j]=rand()%3;                                    
            map[0][0]=TREE;                                            
                                                                
            map[mapSize-1][mapSize-1]=EXIT;
        }
    }

    return map;
}

/*
* Displays the map.
*/
void showMap(int **map, int mapSize, Player player)
{   
    for(int i=0; i < mapSize; ++i)
    {   
        for(int j=0;j < mapSize; ++j)
        {
            //show Player
            if (i == player.position.y && j == player.position.x)
            {
                printf(" %s ", PLAYER_EMOJI);
            }
            else if(map[i][j] == TREE)
            {
                printf(" %s ", TREE_EMOJI);
            }
            else if(map[i][j] == OBSTACLE)
            {
                printf(" %s ", OBSTACLE_EMOJI);
            }
            else if(map[i][j] == FOOD)
            {
                printf(" %s ", FOOD_EMOJI);
            }
            else if(map[i][j] == EXIT)
            {
                printf(" %s ", EXIT_EMOJI);
            }
            
        }
        printf("\n");

    }
}

/*
* @brief Frees the memory allocated for the map.
* @param map The map to free.
* @param mapSize The size of the map.
*/
void freeMap(int** map, int mapSize) {
    for (int i = 0; i < mapSize; i++) {
        free(map[i]);
    }
    free(map);
}

/*
* Function to get the opposite direction of the given direction.
*/
char getOppositeDirection(char direction){
    switch(direction){
        case MOVE_NORTH_INPUT:
            return MOVE_SOUTH_INPUT;
        case MOVE_NORTH_EAST_INPUT:
            return MOVE_SOUTH_WEST_INPUT;
        case MOVE_EAST_INPUT:
            return MOVE_WEST_INPUT;
        case MOVE_SOUTH_EAST_INPUT:
            return MOVE_NORTH_WEST_INPUT;
        case MOVE_SOUTH_INPUT:
            return MOVE_NORTH_INPUT;
        case MOVE_SOUTH_WEST_INPUT:
            return MOVE_NORTH_EAST_INPUT;
        case MOVE_WEST_INPUT:
            return MOVE_EAST_INPUT;
        case MOVE_NORTH_WEST_INPUT:
            return MOVE_SOUTH_EAST_INPUT;
        default:
            return INVALID_DIRECTION_INPUT;
    }
}

int saveMap(int** map, char* saveFileName)
{
    FILE* file = fopen(saveFileName, "wb");
    if (file == NULL) {
        printf("File not found, impossible to save the map. Exiting.");
        return EXIT_FAILURE;
    }

    /* create a static map because you can't save a dynamic one
    * TODO : use a static map in the game instead
    */
    int mapToSave[MAP_SIZE][MAP_SIZE];

    for (unsigned int i = 0; i < MAP_SIZE; i++)
    {
        for(unsigned int j = 0; j < MAP_SIZE; j++)
        {
            mapToSave[i][j] = map[i][j];
        }
    }

    fwrite(mapToSave, sizeof(int), MAP_SIZE * MAP_SIZE, file);

    return fclose(file);
}

int loadMap(int** map, char* saveFileName)
{
    FILE* file = fopen(saveFileName, "rb");
    if (file == NULL) {
        printf("File not found, impossible to load the map. Creating a new one.");
        return EXIT_FAILURE;
    }

    // load a static map
    int loadMap[MAP_SIZE][MAP_SIZE];
    fread(loadMap, sizeof(int), MAP_SIZE * MAP_SIZE, file);

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

    return fclose(file);

}