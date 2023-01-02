/**
 * @file Save.c
 * @brief File containing the functions to handle the save and load of the game.
 * @author Charles-Meldhine Madi Mnemoi
*/

#include "./include/Save.h"

/**
 * @brief Show a menu allowing the player to choose a save slot.
 * @return The save slot chosen by the player.
*/
char chooseSaveSlot()
{
    char saveSlot;
    int saveSlotIsValid = false;

    while (!saveSlotIsValid)
    {
        printf("Choose a save slot to save/load the game (1-3): ");
        saveSlot = getPlayerInput();

        if (saveSlot == '1' || saveSlot == '2' || saveSlot == '3')
        {
            saveSlotIsValid = true;
        }
        else
        {
            printf("Invalid save slot, please try again.\n");
        }
    }

    printf("Save slot %c chosen.\n", saveSlot);

    return saveSlot;
}