/**
* File which handles the Map structure and functions.
*/

#include "./include/Map.h"

/*
* Generates a mapSize x mapSize map.
*/
int **generateMap(int mapSize){
    int** map;
    int nbEmptySquare,nbObstacle;
    int choix;
    double FoodRatio,ObstacleRatio;


    map=malloc(mapSize * sizeof(int*));

    for (int i=0; i< mapSize; i++)
    {
        map[i]=malloc(mapSize * sizeof(int));
    }
        
    for(int i=0; i<mapSize; i++)
    {
        for(int j=0 ; j<mapSize; j++)
        {
            map[i][j]=rand()%2;
            if (map[i][j]==0)
            { 
                nbEmptySquare++;
            }
            else
            {
                nbObstacle++;
            }
        } 
    } 
    printf("Choisissez la difficulté du labyrinte :\n");
    printf("1. Facile (peu d'obstacles)\n");
    printf("2. Moyen (un nombre moyen d'obstacles)\n");
    printf("3. Difficile (beaucoup d'obstacles)\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    if (choix == 1)
    {
    FoodRatio = 0.7;
    ObstacleRatio = 1.4;
    }
    else if (choix == 2)
    {
    FoodRatio = 0.7;
    ObstacleRatio = 0.4;
    }
    else 
    {
    FoodRatio = 0.4;
    ObstacleRatio = 0.1;
    }

    int nbBonus=nbEmptySquare*FoodRatio; 
    int nbMalus=nbObstacle*ObstacleRatio;
    while(nbBonus>0 || nbMalus>0)
    {
        int line = rand() % mapSize;
        int column= rand() % mapSize;

        if ((map[line][column]==TREE))
        {
            map[line][column]=FOOD;
            nbBonus--;
        }
        else
        {
            map[line][column]=TREE;
            nbMalus--;
        }
    } 
    map[0][0]=TREE; 
    map[mapSize-1][mapSize-1]=EXIT;
    
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