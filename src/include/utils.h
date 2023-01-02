/**
 * @file utils.h
 * @brief Functions prototypes to handle the utils.
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

int kbhit(void);
char getPlayerInput();

#endif