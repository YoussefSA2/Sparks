/**
 * @file Map.h
 * @brief Functions prototypes to handle the map.
 * @authors Charles-Meldhine Madi Mnemoi, Dean Bah
*/

#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "./Constants.h"
#include "./Path.h"
#include "./Player.h"
#include "./utils.h"

#define TREE 0
#define TREE_EMOJI "🌲"
#define OBSTACLE 1
#define OBSTACLE_EMOJI "🚧"
#define FOOD 2
#define FOOD_EMOJI "🍎"
#define EXIT 3
#define EXIT_EMOJI "🏁"
#define PLAYER_EMOJI "👨"

int **generateMap(int mapSize, char mapDifficulty);
char getOppositeDirection(char direction);
void freeMap(int** map, int mapSize);
void showMap(int** map, int mapSize, Player player);
int** generateReplayMap(int** savedMap, cvector_vector_type(Coordinates) movesHistory);
void removeEatenFoodFromReplayMap(int** replayMap, Coordinates position);

#endif