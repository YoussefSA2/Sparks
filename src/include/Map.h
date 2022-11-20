#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./Constants.h"
#include "./Player.h"

#ifdef _WIN32
    #include <conio.h>

    #define TREE 0
    #define TREE_EMOJI "T"
    #define OBSTACLE 1
    #define OBSTACLE_EMOJI "O"
    #define FOOD 2
    #define FOOD_EMOJI "F"
    #define PLAYER_EMOJI "P"
#else
    #define TREE 0
    #define TREE_EMOJI "🌲"
    #define OBSTACLE 1
    #define OBSTACLE_EMOJI "🚧"
    #define FOOD 2
    #define FOOD_EMOJI "🍎"
    #define PLAYER_EMOJI "👨"
#endif


int **generateMap(int mapSize);
char getOppositeDirection(char direction);
void showMap(int** map, int mapSize, Player player);   

#endif