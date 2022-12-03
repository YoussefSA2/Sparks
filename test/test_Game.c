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

void test_setup(void) {
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
    mu_assert(saveGame() == GAME_IS_FINISHED, "saveGame should return GAME_IS_FINISHED");
}

MU_TEST(test_handle_player_input_exit) {
    mu_assert(handlePlayerInput(EXIT_INPUT, &player, map) == GAME_IS_FINISHED, "handlePlayerInput should return GAME_IS_FINISHED");
}

MU_TEST(test_handle_player_input_unvalid_move) {
	// Player is initialized at (0, 0) so they shouldn't be able go west
	mu_assert(handlePlayerInput(MOVE_WEST_INPUT, &player, map) == INVALID_DIRECTION_INPUT, "handlePlayerInput should return INVALID_DIRECTION_INPUT");
}

MU_TEST(test_handle_player_input_valid_move) {
	// Player is initialized at (0, 0) so they should be able go south
	mu_assert(handlePlayerInput(MOVE_SOUTH_INPUT, &player, map) == MOVE_SUCCESS, "handlePlayerInput should return MOVE_SUCCESS");
}

MU_TEST(test_handle_player_input_food_found) {
	// there is food at (0, 1) so the player shoudld find it by going east
	mu_assert(handlePlayerInput(MOVE_EAST_INPUT, &player, map) == FOOD_FOUND, "handlePlayerInput should return FOOD_FOUND");
}

MU_TEST(test_handle_player_input_obstacle_found) {
	player.position.x = 1;
	// there is an obstacle at (0, 2) so the player should hit it by going east
	mu_assert(handlePlayerInput(MOVE_EAST_INPUT, &player, map) == OBSTACLE_HIT, "handlePlayerInput should return OBSTACLE_HIT");
}

MU_TEST(test_handle_player_input_random) {
	mu_assert(handlePlayerInput(RANDOM_INPUT, &player, map) == GAME_IS_RUNNING, "handlePlayerInput should return GAME_IS_RUNNING");
}

MU_TEST(test_check_game_state_player_won){
	int lastPlayerAction = 11;

	player.position.x = MAP_SIZE - 1;
	player.position.y = MAP_SIZE - 1;
	
	int result = checkGameState(player, lastPlayerAction);

	mu_assert(result == PLAYER_WON, "checkGameState should return PLAYER_WON");
}

MU_TEST(test_check_game_state_player_is_still_alive){
	int lastPlayerAction = 11;

	player.position.x = 0;
	player.position.y = 0;
	
	int result = checkGameState(player, lastPlayerAction);

	mu_assert(result == lastPlayerAction, "checkGameState should return lastPlayerAction");
}

MU_TEST(test_check_game_state_player_lost){
	int lastPlayerAction = 11;

	player.energy = -1;

	int result = checkGameState(player, lastPlayerAction);

	mu_assert(result == PLAYER_LOST, "checkGameState should return playerLost");
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

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}