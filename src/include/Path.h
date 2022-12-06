//prevent auto-include
#ifndef PATH_H
#define PATH_H

#include "./Constants.h"
#include "./Coordinates.h"

Coordinates* getShortestPathToExit(int** map);
#endif