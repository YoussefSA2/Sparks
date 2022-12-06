/*
* Main file, contains the game loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Game.h"
#include "./include/Map.h"
#include "./include/Player.h"
#include <time.h> 

/*
* Main function, contains the game loop.
*/
int main(void)
{
    srand(time(NULL)) ;
    int lastPlayerAction = GAME_IS_RUNNING;

    int** map = generateMap(MAP_SIZE);
    Player player = initPlayer();

    showMap(map, MAP_SIZE, player);

  
    while(lastPlayerAction != GAME_IS_FINISHED)
    {   
        #ifdef _WIN32 // Windows
            if (kbhit()) {
                lastPlayerAction = handlePlayerInput(getPlayerInput(), &player, map);
                clearScreen();
                showMap(map, MAP_SIZE, player);
                printLastAction(lastPlayerAction);
                checkGameState(player, lastPlayerAction);
            }
        #else
            lastPlayerAction = handlePlayerInput(getPlayerInput(), &player, map);
            clearScreen();
            showMap(map, MAP_SIZE, player);
            printLastAction(lastPlayerAction);
            checkGameState(player, lastPlayerAction);
        #endif
    }

    clearScreen();
    printLastAction(lastPlayerAction);
    printf("Thanks for playing!\n");

    return EXIT_SUCCESS;
}