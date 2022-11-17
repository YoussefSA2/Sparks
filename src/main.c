#include <stdio.h>
#include <stdlib.h>
#include "./Map.h"

int main(void)
{
    printf("Hello World!\n");

    int gameFinished = 0;

    int N=3;
    int M=3;

    while(!gameFinished)
    {
        int** map = genererMatrice(N, M);
        gameFinished = 1;
    }

    return 0;
}