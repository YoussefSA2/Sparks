/*
* Main file, contains the game loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Game.h"
#include "./include/Map.h"
#include "./include/Player.h"

void mainGameLoop(Player* player, int** map)
{
    int gameIsFinished = false;

    while(!gameIsFinished){
        int lastPlayerAction;
        lastPlayerAction = handlePlayerInput(getPlayerInput(), player, map);
        clearScreen();
        showMap(map, MAP_SIZE, *(player));
        printLastAction(lastPlayerAction);
        displayAvailableCommands();
        gameIsFinished = checkGameState(*(player), lastPlayerAction, map);
    }
}

/*
* Main function, contains the game loop.
*/
int main(void)
{
    showMenu();
    int lastPlayerAction = GAME_IS_RUNNING;
    int gameIsFinished = false;

    int** map = generateMap(MAP_SIZE);
    Player player = initPlayer();
    char playerInput;
    #ifdef _WIN32
        if (kbhit()) {
            playerInput = getPlayerInput();
            choiceMenu(playerInput, &player, map, "player.sav", "map.sav");
            mainGameLoop(&player, map);
        }
    #else
        playerInput = getPlayerInput();
        choiceMenu(playerInput, &player, map, "player.sav", "map.sav");
        showMap(map, MAP_SIZE, player);
        mainGameLoop(&player, map);
    #endif

    printf("Thanks for playing!\n");
    freeMap(map, MAP_SIZE);

    return EXIT_SUCCESS;
}