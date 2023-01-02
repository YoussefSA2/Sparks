/**
 * @file console.h
 * @brief Functions prototypes to handle the user interactions with the console.
 * @author Charles-Meldhine Madi Mnemoi, Youssef Saidi
*/

#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

void clearScreen();
int kbhit(void);
char getPlayerInput();

#endif