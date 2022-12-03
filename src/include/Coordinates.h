#ifndef _COORDINATES_H
#define _COORDINATES_H

#include <stdio.h>

typedef struct Coordinates Coordinates;
struct Coordinates {
    int x;
    int y;
};

void showCoordinates(Coordinates coordinates);

#endif
