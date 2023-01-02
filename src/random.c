/**
 * @file random.c
 * @brief File containing functions to generate random numbers.
 * @author Charles-Meldhine Madi Mnemoi
*/

#include "./include/random.h"

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