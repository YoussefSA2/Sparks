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

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_save_game);
    MU_RUN_TEST(test_handle_player_input_exit);
	MU_RUN_TEST(test_handle_player_input_unvalid_move);
	MU_RUN_TEST(test_handle_player_input_valid_move);
	MU_RUN_TEST(test_handle_player_input_food_found);
	MU_RUN_TEST(test_handle_player_input_obstacle_found);
	MU_RUN_TEST(test_handle_player_input_random);

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}