/**
* File which handles the Map structure and functions.
*/

#include "./include/Map.h"

/*
* Generates a mapSize x mapSize map.
*/
int **generateMap(int mapSize){
    int** map;

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