#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./Constants.h"
#include "./Player.h"

#define TREE 0
#define TREE_EMOJI "🌲"
#define OBSTACLE 1
#define OBSTACLE_EMOJI "🚧"
#define FOOD 2
#define FOOD_EMOJI "🍎"
#define EXIT 3
#define EXIT_EMOJI "🏁"
#define PLAYER_EMOJI "👨"

int **generateMap(int mapSize);
char getOppositeDirection(char direction);
void freeMap(int** map, int mapSize);
void showMap(int** map, int mapSize, Player player);
void saveMap(int** map, FILE* saveFile);
void loadMap(int** map, FILE* saveFile);
int** generateReplayMap(int** savedMap, cvector_vector_type(Coordinates) movesHistory);
void removeEatenFoodFromReplayMap(int** replayMap, Coordinates position);

#endif