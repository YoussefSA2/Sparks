/**
 * @file Coordinates.c
 * @brief Coordinates functions.
 * @authors Sithursha Sivathevan, Charles-Meldhine Madi Mnemoi
 * 
 * @details This file contains the functions to manipulate Coordinates 
 * which are used to represent a position on the map.
*/

#include "./include/Coordinates.h"

/**
 * @brief Display the coordinates of a position.
 * @param position The coordinates of the position.
 * 
*/
void showCoordinates(Coordinates position){
    printf("(%d, %d)", position.x, position.y);
}

/**
 * @brief Check if two positions are equal.
 * @param position1 The coordinates of the first position.
 * @param position2 The coordinates of the second position.
 * @return true if the two positions are equal, false otherwise.
*/
int areEqual(Coordinates position1, Coordinates position2){
    return position1.x == position2.x && position1.y == position2.y;
}
