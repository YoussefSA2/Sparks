/**
 * @file Path.h
 * @brief Functions prototypes to handle the pathfinding.
 * @author Charles-Meldhine Madi Mnemoi
*/

#ifndef PATH_H
#define PATH_H

#include "./Constants.h"
#include "./Coordinates.h"
#include "./cvector.h"
#include "./CoordinatesQueue.h"
#include "./Map.h"

cvector_vector_type(Coordinates) getShortestPathToExit(int** map, int mapSize);
#endif