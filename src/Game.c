/*
* File containing all the functions needed to handle the game in its main loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./include/Game.h"

/*
* @brief Save the game
* 
*/
int saveGame(Player* player, int** map) {
    
    savePlayer(player, "player.sav");
    saveMap(map, "map.sav");
    
    return PLAYER_SAVED;
}

/*
* Clears the console.
*/
void clearScreen()
{
    system("clear");
}

/*
* Returns the player input.
*/
char getPlayerInput() {
    
    char input = getchar();
    getchar(); // To remove the \n character you get when you press enter
    return input;
    
}

/*
* Fonction which checks if the player is still on the map after moving. 
*/
int isPlayerInTheMap(Player* player, int mapSize) {
    if (player->position.x < 0 || player->position.x >= mapSize || player->position.y < 0 || player->position.y >= mapSize) {
        return false;
    }
    return true;
}

/*
* Fonction which handles player movement.
* It checks if the player is still on the map after moving (if not, they go back to their previous position).
* and change player energy given the destination square (tree, food, obstacle).
* If player find food, it increases their energy and removes the food from the map.
* If player hit an obstacle, it decreases their energy and player goes back to their previous position.
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

/*
* Function which handles all player inputs.
* It calls the functions corresponding to the player input.
* For example, if the player inputs 'q', it will call the saveGame function, etc.
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

/*
* Function which prints the last action the player did.
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

int killPlayer()
{
    printf("You lost ! You don't have energy anymore.\n");

    return PLAYER_LOST;
}

int handlePlayerVictory() 
{
    printf("You've reached the exit, you win!\n");
    return PLAYER_WON;
}

/*
* Function which displays available commands
*/
void displayAvailableCommands(){
    printf("[7] GO NORTH WEST [8] GO NORTH [9] GO NORTH EAST ");
    printf("[4] GO WEST [6] GO EAST ");
    printf("[1] GO SOUTH WEST [2] GO SOUTH [3] GO SOUTH EAST [q] SAVE GAME\n");
}

void loadGame(Player* player, int** map, char* playerSaveFile, char* mapSaveFile)
{
    loadPlayer(player, playerSaveFile);
    loadMap(map, mapSaveFile);
}

void showMenu(){
    printf("Que voulez-vous faire?\n");
    printf("1: Une nouvelle partie\n");
    printf("2: Charger le jeu\n");
}

void choiceMenu(char playerInput, Player* player, int** map, char* playerSaveFile, char* mapSaveFile){
    if(playerInput=='1'){
        return;
    }    
    else if(playerInput=='2'){
        loadGame(player, map, playerSaveFile, mapSaveFile);
        return;
    }       
}