/**
* File which handles the Map structure and functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#ifdef _WIN32
    #define OBSTACLE "x"
    #define TREE "*"
#else
    #define OBSTACLE "🚧"
    #define TREE "🌲"
#endif

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
void showMap(int **map, int map_size)
{
    for(int i=0; i < map_size; ++i)
    {   
        for(int j=0;j < map_size; ++j)
        {
            printf(" %s ", (map[i][j]==0) ? TREE:OBSTACLE);
        }
        printf("\n");

    }
}