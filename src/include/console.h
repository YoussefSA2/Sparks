/**
 * @file console.h
 * @brief Functions prototypes to handle the user interactions with the console.
 * @author Charles-Meldhine Madi Mnemoi, Youssef Saidi
*/

#ifndef UTILS_H
#define UTILS_H

#include <conio.h>
#include <stdlib.h>
#include <time.h>

void clearScreen();
char getPlayerInput();
unsigned int randomInteger(unsigned int min, unsigned int max);


#endif