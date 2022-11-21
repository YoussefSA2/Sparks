#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "./Player.h"


#ifdef _WIN32
    #include <conio.h>
    #define OBSTACLE "x"
    #define PLAYER "P"
    #define TREE "*"
#else
    #define OBSTACLE "🚧"
    #define PLAYER "👨"
    #define TREE "🌲"
#endif


int **generateMap(int MAP_SIZE);
void showMap(int** map, int map_size, Player player);   

#endif