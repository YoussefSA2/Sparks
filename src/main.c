#include <stdio.h>
#include <stdlib.h>
#include "./include/Map.h"

int main(void)
{
    int gameFinished = 0;

    int N=3;
    int M=3;

    while(!gameFinished)
    {
        int** map = generateMap(N, M);
        showMap(map, N);
        gameFinished = 1;
    }

    return 0;
}