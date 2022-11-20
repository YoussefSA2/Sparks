#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./Constants.h"
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


int **generateMap(int mapSize);
char getOppositeDirection(char direction);
void showMap(int** map, int mapSize, Player player);   

#endif