/**
 * @brief File which handles the Map structure and functions.
 * @authors Dean Bah, Charles-Meldhine Madi Mnemoi
*/

#include "./include/Map.h"

/**
 * @brief Generates a mapSize x mapSize map.
 * @param mapSize The size of the map.
 * @param mapDifficulty The difficulty of the map.
 * @return A pointer to the generated map.
 * 
 * This function allocates memory for a mapSize x mapSize map, 
 * and fills it with obstacles and food according to the mapDifficulty.
*/
int** generateMap(int mapSize, char mapDifficulty){
   
    // Allocate memory for the map
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
            map[i][j]=TREE;
        } 
    } 
    
    // Fill the map with obstacles and food

    // The number of obstacles and food is calculated according to the mapDifficulty
    double foodRatio;
    double obstacleRatio;

    switch(mapDifficulty)
    {
        case EASY:
            foodRatio = EASY_FOOD_RATIO;
            obstacleRatio = EASY_OBSTACLE_RATIO;
            break;
        case NORMAL:
            foodRatio = NORMAL_FOOD_RATIO;
            obstacleRatio = NORMAL_OBSTACLE_RATIO;
            break;
        case HARD:
            foodRatio = HARD_FOOD_RATIO;
            obstacleRatio = HARD_OBSTACLE_RATIO;
            break;
        default:
            printf("We shouldn't be here, exiting game.\n");
            exit(EXIT_FAILURE);
    }

    int nbBonuses = (int) (NUMBER_OF_SQUARES * foodRatio);
    int nbMaluses = (int) (NUMBER_OF_SQUARES * obstacleRatio);

    // We fill the map with obstacles and food
    do {
        
        for (int i = 0; i < nbMaluses; i++)
        {
            int x = randomInteger(0, mapSize - 1);
            int y = randomInteger(0, mapSize - 1);
            // if the square is already an obstacle, we rewind the loop
            // so we are sure to have the exact number of obstacles we want
            if (map[y][x] == OBSTACLE)
            {
                i--;
            }
            else
            {
                map[y][x] = OBSTACLE;
            }
        }

        for (int i = 0; i < nbBonuses; i++)
        {
            int x = randomInteger(0, mapSize - 1);
            int y = randomInteger(0, mapSize - 1);
            // if the square is already an obstacle or food, we rewind the loop
            // so we don't remove the obstacle and we are sure to have the exact number of food we want
            if (map[y][x] == FOOD || map[y][x] == OBSTACLE)
            {
                i--;
            }
            else
            {
                map[y][x] = FOOD;
            }
        }

        map[0][0] = TREE; 
        map[mapSize-1][mapSize-1] = EXIT;

    } while (getShortestPathToExit(map, MAP_SIZE) == NULL); // as long as there is no path to the exit, we generate a new map

    return map;
}

/**
 * @brief Displays the map.
 * @param map The map to display.
 * @param mapSize The size of the map.
 * @param player The player to display on the map.
*/
void showMap(int **map, int mapSize, Player player)
{   
    for(int i=0; i < mapSize; ++i)
    {   
        for(int j=0;j < mapSize; ++j)
        {
            if (i == player.position.y && j == player.position.x)
            {
                printf(" %s ", PLAYER_EMOJI);
            }
            else
            {
                switch(map[i][j])
                {
                    case TREE:
                    printf(" %s ", TREE_EMOJI);
                    break;
                    case OBSTACLE:
                    printf(" %s ", OBSTACLE_EMOJI);
                    break;
                    case FOOD:
                    printf(" %s ", FOOD_EMOJI);
                    break;
                    case EXIT:
                    printf(" %s ", EXIT_EMOJI);
                    break;
                }
            }
        }
        printf("\n");

    }
}

/**
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

/**
 * @brief Function to get the opposite direction of the given direction.
 * @param direction The direction to get the opposite of.
 * @return The opposite direction.
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

/**
 * @brief Function which generates a replay map from a saved map.
 * @param savedMap The saved map.
 * @param movesHistory The moves history of the player.
 * @return The replay map.
 * This function uses player movesHistory to generate the replay map from a saved map,
 * which contains the food that was eaten by the player during the game.
 */
int** generateReplayMap(int** savedMap, cvector_vector_type(Coordinates) movesHistory)
{
    // create a new map
    int** replayMap = malloc(MAP_SIZE * sizeof(int*));
    for (unsigned int i = 0; i < MAP_SIZE; ++i){
        replayMap[i] = malloc(MAP_SIZE * sizeof(int));
    }

    // fill the new map with the saved map data
    for (unsigned int i = 0; i < MAP_SIZE; i++)
    {
        for(unsigned int j = 0; j < MAP_SIZE; j++)
        {
            replayMap[i][j] = savedMap[i][j];
        }
    }
    
    // fill the new map with the moves history data
    unsigned int movesHistorySize = cvector_size(movesHistory);
    for (unsigned int i = 0; i < movesHistorySize; i++)
    {
        if (movesHistory[i].content == FOOD){
            replayMap[movesHistory[i].y][movesHistory[i].x] = FOOD;
        }
    }

    return replayMap;
}

/**
 * @brief Function which removes the eaten food from the replay map.
 * @param replayMap The replay map.
 * @param position The position of the eaten food.
 */
void removeEatenFoodFromReplayMap(int** replayMap, Coordinates position)
{
    if (replayMap[position.x][position.y] == FOOD){
        replayMap[position.x][position.y] = TREE;
    }
}
