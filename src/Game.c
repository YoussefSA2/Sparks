/*
* File containing all the functions needed to handle the game in its main loop.
*/

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
    system("clear");
}

/**
* @brief Returns the player input.
* @return The player input.
*/
char getPlayerInput() {
    while (!kbhit()) {}
    char input = getchar();
    return input;
    
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
        case CANCEL_MOVE_INPUT:
            return cancelMove(player);
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

/*
* Function wich shows statistics of the game
*/
void showStatistics(Player player, int ** map){
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
}

/**
 * @brief Function which prints a message when the player wins.
 * @return PLAYER_WON
*/
int handlePlayerVictory(Player player, int ** map) 
{
    printf("You've reached the exit, you win!\n");
    showStatistics(player, map);
    return PLAYER_WON;
}

/**
 * @brief Function which displays the available commands to the player.
*/
void displayAvailableCommands(){
    printf("[7] GO NORTH WEST [8] GO NORTH [9] GO NORTH EAST");
    printf("[4] GO WEST [6] GO EAST ");
    printf("[1] GO SOUTH WEST [2] GO SOUTH [3] GO SOUTH EAST [q] SAVE GAME [c] CANCEL PREVIOUS MOVE\n");
}

/**
 * @brief Function which displays the main menu of the game.
*/
void mainMenu(){    
    printf("Welcome to our game!\n");
    printf("What do you want to do?\n");
    printf("1: New game\n");
    printf("2: Load previous game\n");
    printf("3: Replay last game\n");
    printf("q: Quit\n");
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
 * @brief Function which displays the replay of the last game.
 * @param player The player.
 * @param map The map.
 * @param replaySpeed The speed of the replay in seconds.
 * @return INVALID_LAUNCH_GAME_CHOICE if the game is not finished and END_REPLAY if the replay is launched successfully.
*/
int showReplay(Player player, int** map, int replaySpeed){
    loadGame(&player, map);

    int playerWon = player.position.x == MAP_SIZE-1
     && player.position.y == MAP_SIZE-1;
    int playerLost = player.energy <= 0;
    int gameIsFinished = playerWon || playerLost;

    if (!gameIsFinished){
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
 * @brief Function which displays the map difficulty menu.
*/
void mapDifficultyMenu(){
    printf("Choose a difficulty:\n");
    printf("1: Easy (a few obstacles)\n");
    printf("2: Normal (an average amount of obstacles)\n");
    printf("3: Hard (a lot of obstacles)\n");
}

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
 * @brief Function which launches the game. It calls the loadGame function if the user wants to load a previous game.
 * @param playerInput The player input
 * @param player The player struct which might be loaded
 * @param map The map which might be loaded
*/
int launchGame(char playerInput, Player* player, int** map){
    
    switch (playerInput)
    {
        case NEW_GAME:
            map = generateMap(MAP_SIZE, chooseMapDifficulty());
            printf("New game started.\n");
        break;
        case LOAD_GAME:
            if(loadGame(player, map) != GAME_LOAD_FAILED){
                printf("Previous game loaded.\n");
            }
            break;
        case REPLAY_GAME:
            return showReplay(*player, map, chooseReplaySpeed());
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