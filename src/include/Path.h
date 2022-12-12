//prevent auto-include
#ifndef PATH_H
#define PATH_H

#include "./Constants.h"
#include "./Coordinates.h"

cvector_vector_type(Coordinates) getShortestPathToExit(int** map, int mapSize);
#endif