#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#ifdef _WIN32
    #include <conio.h>
    #define OBSTACLE "x"
    #define TREE "*"
#else
    #define OBSTACLE "🚧"
    #define TREE "🌲"
#endif


int **generateMap(int MAP_SIZE);
void showMap(int** map, int map_size);

#endif