#include <stdlib.h>
#include "./include/minunit.h"
#include "../src/include/Game.h"
#include "../src/include/Map.h"
#include "../src/include/Player.h"

/*
* Game states
*/

#define RANDOM_INPUT 'r'

Player player;
int **map = NULL;
int gameIsFinished;

void test_setup(void) {
	
	gameIsFinished = false;
	player = initPlayer();

	map = generateMap(10);
	map[1][0] = TREE;
	map[0][1] = FOOD;
	map[0][2] = OBSTACLE;
}

void test_teardown(void) {
	/* Nothing */
}

MU_TEST(test_save_game) {
    mu_assert(saveGame(&player, map) == PLAYER_SAVED, "saveGame should return PLAYER_SAVED");
}

MU_TEST(test_handle_player_input_exit) {
    mu_assert(handlePlayerInput(EXIT_INPUT, &player, map) == PLAYER_SAVED, "handlePlayerInput should return GAME_IS_FINISHED");
}

MU_TEST(test_handle_player_input_unvalid_move) {
	// Player is initialized at (0, 0) so they shouldn't be able go west
	mu_assert(handlePlayerInput(MOVE_WEST_INPUT, &player, map) == INVALID_DIRECTION_INPUT, "handlePlayerInput should return INVALID_DIRECTION_INPUT");
}

MU_TEST(test_handle_player_input_valid_move) {
	// Player is initialized at (0, 0) so they should be able go south
	mu_assert(handlePlayerInput(MOVE_SOUTH_INPUT, &player, map) == MOVE_SUCCESS, "handlePlayerInput should return MOVE_SUCCESS");
	
	mu_assert(player.movesHistory[1].x == 1, "player.movesHistory should contains (1,0)");
	mu_assert(player.movesHistory[1].y == 0, "player.movesHistory should contains (1,0)");	
}

MU_TEST(test_handle_player_input_food_found) {
	// there is food at (1,0) so the player shoudld find it by going east
	mu_assert(handlePlayerInput(MOVE_EAST_INPUT, &player, map) == FOOD_FOUND, "handlePlayerInput should return FOOD_FOUND");
}

MU_TEST(test_handle_player_input_obstacle_found) {
	player.position.x = 1;
	// there is an obstacle at (2, 0) so the player should hit it by going east
	mu_assert(handlePlayerInput(MOVE_EAST_INPUT, &player, map) == OBSTACLE_HIT, "handlePlayerInput should return OBSTACLE_HIT");
}

MU_TEST(test_handle_player_input_random) {
	mu_assert(handlePlayerInput(RANDOM_INPUT, &player, map) == GAME_IS_RUNNING, "handlePlayerInput should return GAME_IS_RUNNING");
}

MU_TEST(test_check_game_state_player_won){
	int lastPlayerAction = 11;

	player.position.y = MAP_SIZE - 1;
	player.position.x = MAP_SIZE - 1;
	
	int result = checkGameState(player, lastPlayerAction, map);

	mu_assert(result == true, "checkGameState should return true");
}

MU_TEST(test_check_game_state_player_is_still_alive){
	int lastPlayerAction = 11;

	player.position.y = 0;
	player.position.x = 0;
	
	int result = checkGameState(player, lastPlayerAction, map);

	mu_assert(result == false, "checkGameState should return false");
}

MU_TEST(test_check_game_state_player_lost){
	int lastPlayerAction = 11;

	player.energy = -1;

	int result = checkGameState(player, lastPlayerAction, map);

	mu_assert(result == true, "checkGameState should return true");
}

MU_TEST(test_check_game_state_player_saved){
	int lastPlayerAction = PLAYER_SAVED;

	int result = checkGameState(player, lastPlayerAction, map);

	mu_assert(result == true, "checkGameState should return true");
}

MU_TEST(test_movesHistory_after_valid_move) {
	// make player move south
	handlePlayerInput(MOVE_SOUTH_INPUT, &player, map);
	
	mu_assert(player.movesHistory[1].x == 1, "player.movesHistory[1] should contains (1,0)");
	mu_assert(player.movesHistory[1].y == 0, "player.movesHistory[1] should contains (1,0)");	
}

MU_TEST(test_movesHistory_if_player_gets_out_of_the_map){
	handlePlayerInput(MOVE_NORTH_INPUT, &player, map);

	mu_assert(cvector_size(player.movesHistory) == 1, "player moveHistory should only contains startPosition");

}

MU_TEST(test_movesHistory_after_hitting_obstacle) {
	map[1][0] = OBSTACLE;

	handlePlayerInput(MOVE_SOUTH_INPUT, &player, map);

	mu_assert(cvector_size(player.movesHistory) == 1, "player moveHistory should only contains startPosition");

}

MU_TEST(test_load_game)
{
	//informations to save
	player.energy = 50;
	player.position = (Coordinates) {1, 3};
	cvector_push_back(player.movesHistory, ((Coordinates) {0,2}));

	map[1][0] = TREE;
	map[0][1] = FOOD;
	map[0][2] = OBSTACLE;

	saveGame(&player, map);

	//modify infos so we can check that the game correctly loads infos above
	player.energy = 0;
	player.position = (Coordinates) {0,0};
	player.movesHistory = NULL;

	map[1][0] = FOOD;
	map[0][1] = OBSTACLE;
	map[0][2] = TREE;

	loadGame(&player, map);

	mu_assert(player.energy == 50, "player.energy should be 50");
	mu_assert(areEqual(player.position, (Coordinates) {1, 3}), "player.position should be (1,3)");
	mu_assert(areEqual(player.movesHistory[1], (Coordinates) {0,2}), "player.movesHistory[1] should contains (0,2)");
	mu_assert_int_eq(cvector_size(player.movesHistory), 2); //start position + 1 move
	mu_assert_int_eq(map[1][0], TREE);
	mu_assert_int_eq(map[0][1], FOOD);
	mu_assert_int_eq(map[0][2], OBSTACLE);
}


MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_save_game);
    MU_RUN_TEST(test_handle_player_input_exit);
	MU_RUN_TEST(test_handle_player_input_unvalid_move);
	MU_RUN_TEST(test_handle_player_input_valid_move);
	MU_RUN_TEST(test_handle_player_input_food_found);
	MU_RUN_TEST(test_handle_player_input_obstacle_found);
	MU_RUN_TEST(test_handle_player_input_random);
	MU_RUN_TEST(test_check_game_state_player_won);
	MU_RUN_TEST(test_check_game_state_player_is_still_alive);
	MU_RUN_TEST(test_check_game_state_player_lost);
	MU_RUN_TEST(test_check_game_state_player_saved);
	MU_RUN_TEST(test_movesHistory_after_valid_move);
	MU_RUN_TEST(test_movesHistory_after_hitting_obstacle);
	MU_RUN_TEST(test_movesHistory_if_player_gets_out_of_the_map);
	MU_RUN_TEST(test_load_game);

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}