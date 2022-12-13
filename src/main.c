/*
* Main file, contains the game loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include "./include/Game.h"
#include "./include/Map.h"
#include "./include/Player.h"

/*
* Main function, contains the game loop.
*/
int main(void)
{
    showMenu();
    
    int gameIsFinished = false;

    int** map = generateMap(MAP_SIZE);
    Player player = initPlayer();
    
    choiceMenu(getPlayerInput(), &player, map, "player.sav", "map.sav");
    
    showMap(map, MAP_SIZE, player);
  
    while(!gameIsFinished)
    {   
        int lastPlayerAction = handlePlayerInput(getPlayerInput(), &player, map);
        clearScreen();
        showMap(map, MAP_SIZE, player);
        printLastAction(lastPlayerAction);
        displayAvailableCommands();
        gameIsFinished = checkGameState(player, lastPlayerAction, map);
    }

    printf("Thanks for playing!\n");
    freeMap(map, MAP_SIZE);

    return EXIT_SUCCESS;
}