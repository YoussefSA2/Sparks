/**
 * @file Coordinates.h
 * @brief Coordinates structure and functions prototypes.
 * @authors Siursha Sivathevan, Charles-Meldhine Madi Mnemoi
*/

#ifndef _COORDINATES_H
#define _COORDINATES_H

#include <stdio.h>

typedef struct Coordinates Coordinates;
struct Coordinates{
    int x;
    int y;
    int content;
};

int areEqual(Coordinates position1, Coordinates position2);
void showCoordinates(Coordinates coordinates);


#endif
