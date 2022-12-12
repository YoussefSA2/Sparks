#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./Constants.h"
#include "./Player.h"

#include <conio.h>
#define TREE 0
#define TREE_EMOJI "T"
#define OBSTACLE 1
#define OBSTACLE_EMOJI "O"
#define FOOD 2
#define FOOD_EMOJI "F"
#define EXIT 3
#define EXIT_EMOJI "E"

#define PLAYER_EMOJI "P"



int **generateMap(int mapSize);
char getOppositeDirection(char direction);
void freeMap(int** map, int mapSize);
void showMap(int** map, int mapSize, Player player);   

#endif