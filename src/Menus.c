/**
 * @file Menus.c
 * @brief File containing functions to handle the menus of the game.
 * @author Charles-Meldhine Madi Mnemoi, Sithursha Sivathevan
*/

#include "./include/Menus.h"

/**
 * @brief Function which handles the difficulty choice of the player.
 * @return The difficulty chosen by the player.
*/
char chooseMapDifficulty(){
    
    mapDifficultyMenu();
    char playerInput = getPlayerInput();

    switch (playerInput)
    {
        case EASY:
            printf("Easy difficulty chosen.\n");
            return EASY;
            break;
        case NORMAL:
            printf("Normal difficulty chosen.\n");
            return NORMAL;
            break;
        case HARD:
            printf("Hard difficulty chosen.\n");
            return HARD;
            break;
        default:
            printf("Invalid choice, try again.\n");
            return INVALID_DIFFICULTY_CHOICE;
            break;
    }
}

/**
 * @brief Function which allows the player to choose the replay speed.
 * @return The replay speed in seconds.
*/
int chooseReplaySpeed(){
    char replaySpeedChoice = 0;
    replaySpeedMenu();
    replaySpeedChoice = getPlayerInput();

    int replaySpeedInSeconds;
    switch (replaySpeedChoice)
    {
        case SLOW:
            replaySpeedInSeconds = 3;
            break;
        case NORMAL:
            replaySpeedInSeconds = 2;
            break;
        case FAST:
            replaySpeedInSeconds = 1;
            break;
        default:
        break;
    }

    return replaySpeedInSeconds;
}

/**
 * @brief Function which displays the main menu of the game.
*/
void mainMenu(){    
    printf("Welcome to our game!\n");
    printf("What do you want to do?\n");
    printf("1: New game\n");
    printf("2: Load a previous game\n");
    printf("q: Quit\n");
}

/**
 * @brief Function which displays the map difficulty menu.
*/
void mapDifficultyMenu(){
    printf("Choose a difficulty:\n");
    printf("1: Easy (a few obstacles)\n");
    printf("2: Normal (an average amount of obstacles)\n");
    printf("3: Hard (a lot of obstacles)\n");
}

/**
 * @brief Function which displays a menu to choose the replay speed.
*/
void replaySpeedMenu(){
    clearScreen();
    printf("Choose replay speed:\n");
    printf("1: Slow\n");
    printf("2: Normal\n");
    printf("3: Fast\n");
}
