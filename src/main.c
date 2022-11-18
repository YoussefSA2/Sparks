#include <stdio.h>
#include <stdlib.h>
#include "./include/Map.h"

#define MAP_SIZE 10

int main(void)
{
    int gameFinished = 0;


    while(!gameFinished)
    {
        int** map = generateMap(MAP_SIZE);
        showMap(map, MAP_SIZE);
        gameFinished = 1;
    }

    return 0;
}