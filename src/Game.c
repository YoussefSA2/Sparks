/*
* File containing all the functions needed to handle the game in its main loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./include/Game.h"

/**
* @brief Function which saves the game.
* It calls the saveMap and savePlayer functions.
* @param player The player.
* @param map The map.
* @return PLAYER_SAVED.
*/
int saveGame(Player* player, int** map) {
    
    FILE* saveFile = fopen("game.sav", "wb");
    if (saveFile == NULL) {
        printf("Error while creating the save file, impossible to save the game. Exiting.");
        exit(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    saveMap(map, saveFile);
    fclose(saveFile);

    saveFile = fopen("game.sav", "ab");
    if (saveFile == NULL) {
        printf("Error while creating the save file, impossible to save the game. Exiting.");
        exit(EXIT_FAILURE);
        return EXIT_FAILURE;
    }
    savePlayer(player, saveFile);
    fclose(saveFile);

    return PLAYER_SAVED;
}

/**
 * @brief Function which loads the game from the `saveFileName` file.
 * @param player The player to load
 * @param map The map to load
 * @param saveFileName The name of the file where the game is saved
*/
int loadGame(Player* player, int** map)
{
    FILE* saveFile = fopen("game.sav", "rb");
    if (saveFile == NULL) {
        printf("Error while opening the save file, impossible to load the game. Launching a new one.\n");
        return GAME_LOAD_FAILED;
    }
    
    loadMap(map, saveFile);
    loadPlayer(player, saveFile);

    fclose(saveFile);

    return GAME_LOAD_SUCCESS;
}


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

/**
 * @brief Fonction which checks if the player is still on the map after moving. 
 * @param player The player.
 * @param mapSize The size of the map.
 * @return true if the player is still on the map, false otherwise.
*/
int isPlayerInTheMap(Player* player, int mapSize) {
    if (player->position.x < 0 || player->position.x >= mapSize || player->position.y < 0 || player->position.y >= mapSize) {
        return false;
    }
    return true;
}

/**
 * @brief Fonction which handles player movement.
 *  It checks if the player is still on the map after moving (if not, they go back to their previous position).
 *  and change player energy given the destination square (tree, food, obstacle).
 *  If player find food, it increases their energy and removes the food from the map.
 *  If player hit an obstacle, it decreases their energy and player goes back to their previous position.
 * @param player The player.
 * @param direction The direction the player wants to move.
 * @param map The map.
 * @return The result of the player move.
*/
int handlePlayerMove(Player* player, char direction, int** map) {
    move(player, direction);

    if (!isPlayerInTheMap(player, MAP_SIZE)) {
        move(player, getOppositeDirection(direction)); // TODO : in the future, use moveHistory to go back to the previous position.
        return INVALID_DIRECTION_INPUT;
    }

    //save move in player moveHistory
    cvector_push_back(player->movesHistory, player->position);

    modifyEnergy(player, -1);

    int squareContent = map[player->position.y][player->position.x];
    if (squareContent == FOOD) {
        modifyEnergy(player, 10);

        // set a tree after player ate the food
        map[player->position.y][player->position.x] = TREE;

        return FOOD_FOUND;
        
    } else if (squareContent == OBSTACLE) {
        // move back the player and removes its move from the history
        move(player, getOppositeDirection(direction));
        cvector_pop_back(player->movesHistory);

        //remove energy
        modifyEnergy(player, -10);
        return OBSTACLE_HIT;
    }


    return MOVE_SUCCESS;
}

/**
 * @brief Function which handles all player inputs.
 * It calls the functions corresponding to the player input.
 * For example, if the player inputs 'q', it will call the saveGame function, etc.
 * @param input The player input.
 * @param player The player.
 * @param map The map.
 * @return The result of the player input.
*/
int handlePlayerInput(char input, Player* player, int** map) {
    switch (input) {
        case EXIT_INPUT:
            return saveGame(player, map);
        case MOVE_NORTH_INPUT:
        case MOVE_NORTH_EAST_INPUT:
        case MOVE_EAST_INPUT:
        case MOVE_SOUTH_EAST_INPUT:
        case MOVE_SOUTH_INPUT:
        case MOVE_SOUTH_WEST_INPUT:
        case MOVE_WEST_INPUT:
        case MOVE_NORTH_WEST_INPUT:
            return handlePlayerMove(player, input, map);
            break;
        default:
            return GAME_IS_RUNNING;
            break;
    }
}

/**
 * @brief Function which prints the last action the player did.
 * @param gameState The last action the player did.
*/
void printLastAction(char gameState) {
    switch (gameState) {
        case MOVE_SUCCESS:
            printf("You moved successfully.\n");
            break;
        case FOOD_FOUND:
            printf("You found food! You gain 10 energy.\n");
            break;
        case OBSTACLE_HIT:
            printf("You hit an obstacle! You lose 10 energy.\n");
            break;
        case PLAYER_SAVED:
            printf("You saved the game.\n");
            break;
        case INVALID_DIRECTION_INPUT:
            printf("You can't go there! Try again.\n");
            break;
        default:
            printf("Invalid input.\n");
            break;
    }
}

/**
 * @brief Function which checks if the game is finished.
 * @param player The player.
 * @param lastPlayerAction The last action the player did.
 * @param map The map.
 * @return true if the game is finished, false otherwise.
*/
int checkGameState(Player player, int lastPlayerAction, int** map)
{
    int playerWon = player.position.x == MAP_SIZE-1
     && player.position.y == MAP_SIZE-1;

    int playerLost = player.energy <= 0;

    int gameState = 0;
    
    if (playerWon)
    {
        gameState = handlePlayerVictory();
        saveGame(&player, map);
    }
    else if (playerLost)
    {
        gameState = killPlayer();
        saveGame(&player, map);
    }
    else if (lastPlayerAction == PLAYER_SAVED)
    {
        gameState = PLAYER_SAVED;
    }

    int gameIsFinished = gameState == PLAYER_LOST 
            || gameState == PLAYER_WON 
            || gameState == PLAYER_SAVED;

    return gameIsFinished;
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
 * @brief Function which prints a message when the player wins.
 * @return PLAYER_WON
*/
int handlePlayerVictory() 
{
    printf("You've reached the exit, you win!\n");
    return PLAYER_WON;
}

/**
 * @brief Function which displays the available commands to the player.
*/
void displayAvailableCommands(){
    printf("[7] GO NORTH WEST [8] GO NORTH [9] GO NORTH EAST ");
    printf("[4] GO WEST [6] GO EAST ");
    printf("[1] GO SOUTH WEST [2] GO SOUTH [3] GO SOUTH EAST [q] SAVE GAME\n");
}

/**
 * @brief Function which displays the main menu of the game.
*/
void showMenu(){    
    printf("Welcome to our game!\n");
    printf("What do you want to do?\n");
    printf("1: New game\n");
    printf("2: Load previous game\n");
}

/**
 * @brief Function which launches the game. It calls the loadGame function if the user wants to load a previous game.
 * @param playerInput The player input
 * @param player The player struct which might be loaded
 * @param map The map which might be loaded
*/
int launchGame(char playerInput, Player* player, int** map){
    
    switch (playerInput)
    {
        case NEW_GAME:
            printf("New game started.\n");
        break;
        case LOAD_GAME:
            if(loadGame(player, map) != GAME_LOAD_FAILED){
                printf("Previous game loaded.\n");
            }
            break;
        default:
            printf("Invalid choice, try again.\n");
            return INVALID_LAUNCH_GAME_CHOICE;
        break;
    }

    return playerInput;

}