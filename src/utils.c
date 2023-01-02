/**
 * @file utils.c
 * @brief File containing uncategorized functions.
 * @author Charles-Meldhine Madi Mnemoi, Youssef Said
*/

#include "./include/utils.h"

/**
 * @brief Returns a random integer between min and max.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return A random integer between min and max.
*/
unsigned int randomInteger(unsigned int min, unsigned int max)
{
    srand(time(NULL) + rand());
    unsigned int value = rand() % (max - min + 1) + min;
    return value;
}

/**
* @brief Returns the player input.
* @return The player input.
*/
char getPlayerInput() {
    return getch();
}