/**
 * @file Display.c
 * @brief Functions to display basic informations in the console
 * @authors Charles-Meldhine Madi Mnemoi, Sitursha Sivathevan, Marwa Tourabi
*/

#include "./include/Display.h"

/**
 * @brief Function which displays the available commands to the player.
*/
void displayAvailableCommands(){
    printf("[7] GO NORTH WEST [8] GO NORTH [9] GO NORTH EAST");
    printf("[4] GO WEST [6] GO EAST ");
    printf("[1] GO SOUTH WEST [2] GO SOUTH [3] GO SOUTH EAST [q] SAVE GAME [c] CANCEL PREVIOUS MOVE\n");
}

/**
 * @brief Function which prints a message when the player wins.
 * @param player The player.
 * @param map The map.
 * @return PLAYER_WON
*/
int handlePlayerVictory(Player player, int** map) 
{
    printf("You've reached the exit, you win!\n");
    showStatistics(player, map);
    return PLAYER_WON;
}

/**
 * @brief Function which prints a message when the player loses.
 * @return PLAYER_LOST
*/
int killPlayer()
{
    printf("You lost ! You don't have energy anymore.\n");

    return PLAYER_LOST;
}

/**
 * @brief Function which shows statistics of the game if the player wins.
 * @param player The player.
 * @param map The map.
*/
void showStatistics(Player player, int** map){
    printf("Energy left: %f     Energy gained: %f    Energy lost: %f \n", player.energy, player.gainedEnergy, player.lostEnergy);
    printf("\nMove history:\n");

    unsigned int movesHistorySize = cvector_size(player.movesHistory); 

    for(unsigned int i = 0; i < movesHistorySize; i++){
        showCoordinates(player.movesHistory[i]);
        // to separate coordinates when displaying until the last one
        if (i != movesHistorySize - 1){printf(", ");}
    }
    Coordinates* shortPath = getShortestPathToExit(map, MAP_SIZE);

    printf("\nShortest path to exit:\n");

    unsigned int shortPathSize = cvector_size(shortPath); 

    for(unsigned int i = 0; i < shortPathSize; i++){
        showCoordinates(shortPath[i]);
        if (i != shortPathSize - 1){printf(", ");}
    }

    printf("\n");
}