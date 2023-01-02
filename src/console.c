/**
 * @file console.c
 * @brief File containing functions to manipulate the user interactions with the console.
 * @author Charles-Meldhine Madi Mnemoi, Youssef Said
*/

#include "./include/console.h"

/**
 * @brief Function which clears the screen.
 * It uses the system function to call the clear command.
*/
void clearScreen()
{
    system("cls");
}

/**
* @brief Returns the player input.
* @return The player input.
*/
char getPlayerInput() {
    return getch();
}