/**
* File which handles the Map structure and functions.
*/

#include "./include/Map.h"

/*
* Generates a MAP_SIZE x MAP_SIZE map.
*/
int **generateMap(int MAP_SIZE){
    // map est un pointeur sur un liste de pointeurs, d'où int**
    int** map;
    // alloué N pointeurs, N étant le nb de lignes
    map=malloc(MAP_SIZE * sizeof(int*));
    for (int i=0; i< MAP_SIZE; i++){
        //pour chaque ligne de la matrice map[i] allouez m entiers, m étant le nb colones
        map[i]=malloc(MAP_SIZE * sizeof(int));}
        //ici la matrice map est construite en mémoire, donc on peut la remplir
        //remplissage de la matrice
        for(int i=0; i<MAP_SIZE; i++){
            for(int j=0 ; j<MAP_SIZE; j++){
                map[i][j]=rand() %2;                                    
                map[0][0]=0;                                            
                                                                    
                map[MAP_SIZE-1][MAP_SIZE-1]=0;
            }
        }

    return map;
}

/*
* Displays the map.
*/
void showMap(int **map, int map_size, Player player)
{   
    for(int i=0; i < map_size; ++i)
    {   
        for(int j=0;j < map_size; ++j)
        {
            if (i == player.position.y && j == player.position.x)
            {
                printf(" %s ", PLAYER);
            }
            else
            {
                printf(" %s ", (map[i][j]==0) ? TREE:OBSTACLE);
            }
            
        }
            //printf(" %s ", (map[i][j]==0) ? TREE:OBSTACLE);
        
        printf("\n");
    }
}
void generateBonusMalus(int **map, int map_size)
// Count the number of empty square
{
    int count=0;
    int line;
    int column;

    for(int i=0; i < map_size; ++i)
    {  
        for(int j=0;j < map_size; ++j)
            if (map[i][j]==0)
                count++;

    }
    int nbBonus=count*0.2;
    int nbMalus=count*0.2;


    while(nbBonus>0 || nbMalus>0){
        line = rand() % map_size;
        column= rand() % map_size;
        
        if (map[line][column]=0){
            if(nbBonus>0)
                map[line][column]=2;
                nbBonus--;
        }
    
            else{
                map[line][column]=3;
                nbMalus--;

        }
    }
}


