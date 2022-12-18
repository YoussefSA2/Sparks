#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

int kbhit(void);
unsigned int randomInteger(unsigned int min, unsigned int max);

#endif