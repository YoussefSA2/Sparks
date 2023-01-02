/**
 * @file Game.c
 * @brief Main game loop functions.
 * @authors Sithursha Sivathevan, Marwa Tourabi, Charles-Meldhine Madi Mnemoi
 * 
 * @details File containing all the functions needed to handle the game in its main loop.
*/

#include "./include/Game.h"
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

    // on the map, the X and Y coordinates are inverted
    // TODO : find a better way to do this
    Coordinates playerPositionOnTheMap = {player->position.y, player->position.x};

    //save move in player moveHistory
    cvector_push_back(player->movesHistory, playerPositionOnTheMap);

    modifyEnergy(player, -1);

    int squareContent = map[player->position.y][player->position.x];
    player->position.content = squareContent;
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
            return PLAYER_SAVED;
        case MOVE_NORTH_INPUT:
        case MOVE_NORTH_EAST_INPUT:
        case MOVE_EAST_INPUT:
        case MOVE_SOUTH_EAST_INPUT:
        case MOVE_SOUTH_INPUT:
        case MOVE_SOUTH_WEST_INPUT:
        case MOVE_WEST_INPUT:
        case MOVE_NORTH_WEST_INPUT:
            return handlePlayerMove(player, input, map);
        case CANCEL_MOVE_INPUT:
            return cancelMove(player);
            break;
        default:
            return GAME_IS_RUNNING;
            break;
    }
}

/**
 * @brief Function which checks if the game is finished.
 * @param player The player.
 * @return true if the game is finished, false otherwise.
*/
int isGameFinished(Player player) {
    int playerWon = player.position.x == MAP_SIZE - 1
     && player.position.y == MAP_SIZE - 1;
    int playerLost = player.energy <= 0;

    return playerWon || playerLost;
}

/**
 * @brief Function which prints the last action the player did.
 * @param gameState The result of the last action the player did.
*/
void printLastAction(char gameState, Player player) {
    showPlayerEnergy(player);
    showPlayerPosition(player);

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
        case CANCEL_MOVE_SUCCESS:
            printf("The move was canceled successfully.\n");
            break;
        case PLAYER_SAVED:
            printf("You saved the game.\n");
            break;
        case INVALID_DIRECTION_INPUT:
            printf("You can't go there! Try again.\n");
            break;
        case NO_REWINDS_LEFT:
            printf("No more rewinds.\n");
            break;
        case NO_MOVE_TO_CANCEL:
            printf("No move to cancel : you haven't moved yet!\n");
            break;
        default:
            printf("Invalid input.\n");
            break;
    }

    if (alreadyPassedOn(&player)) {
        printf("You already passed on this square, be careful!\n");
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
        gameState = handlePlayerVictory(player, map);
    }
    else if (playerLost)
    {
        gameState = killPlayer();
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
 * @brief Function which displays the replay of the last game.
 * @param player The player.
 * @param map The map.
 * @param replaySpeed The speed of the replay in seconds.
 * @param saveSlot The save slot number.
 * @return INVALID_LAUNCH_GAME_CHOICE if the game is not finished,
 * END_REPLAY if the replay is launched successfully.
*/
int showReplay(Player player, int** map, int replaySpeed, char saveSlot){
    loadGame(&player, map, saveSlot);

    if (!isGameFinished(player)){
        printf("The previous game is not finished, no replay available.\n");
        return INVALID_LAUNCH_GAME_CHOICE;
    }

    int** replayMap = generateReplayMap(map, player.movesHistory);

    for (unsigned int i = 0; i < cvector_size(player.movesHistory); i++)
    {
        Coordinates replayedPosition = player.movesHistory[i];
        player.position = (Coordinates) {replayedPosition.y, replayedPosition.x}; // x and y are inverted in the replay map
        clearScreen();
        showMap(replayMap, MAP_SIZE, player);
        sleep(replaySpeed);
        removeEatenFoodFromReplayMap(replayMap, replayedPosition);
    }

    printf("Replay finished, coming back to main menu.\n");

    return END_REPLAY;

}

/**
 * @brief Function which launches the game. It calls the loadGame function if the user wants to load a previous game.
 * @param playerInput The player input
 * @param player The player struct which might be loaded
 * @param mapPointer The pointer to the map which might be loaded
 * @return The player choice.
*/
int launchGame(char playerInput, Player* player, int*** mapPointer){
    
    switch (playerInput)
    {
        char difficulty;
        case NEW_GAME:
            do{
                difficulty = chooseMapDifficulty();
            } while(difficulty == INVALID_DIFFICULTY_CHOICE);
            
            // need to pass the map with a pointer to be able to modify it
            *mapPointer = generateMap(MAP_SIZE, difficulty);

            printf("New game started.\n");
        break;
        case LOAD_GAME:
            if(loadGame(player, *(mapPointer), chooseSaveSlot()) != GAME_LOAD_FAILED){
                if(isGameFinished(*player)){
                    printf("The game is already finished, you can resume it. Returning to main menu.\n\n");
                    return INVALID_LAUNCH_GAME_CHOICE;
                }
            }
            break;
        case REPLAY_GAME:
            return showReplay(*player, *(mapPointer), chooseReplaySpeed(), chooseSaveSlot());
        case EXIT_INPUT:
            printf("Bye bye!\n");
            exit(EXIT_SUCCESS);
        default:
            printf("Invalid choice, try again.\n");
            return INVALID_LAUNCH_GAME_CHOICE;
        break;
    }

    return playerInput;

 
}