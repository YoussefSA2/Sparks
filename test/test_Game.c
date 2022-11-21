#include <stdlib.h>
#include "./include/minunit.h"
#include "../src/include/Game.h"
#include "../src/include/Player.h"

/*
* Game states
*/

#define RANDOM_INPUT 'r'

Player player;

void test_setup(void) {
	player = initPlayer();
}

void test_teardown(void) {
	/* Nothing */
}

MU_TEST(test_save_game) {
    mu_assert(saveGame() == GAME_IS_FINISHED, "saveGame should return GAME_IS_FINISHED");
}

MU_TEST(test_handle_player_input_exit) {
    mu_assert(handlePlayerInput(EXIT_INPUT, &player) == GAME_IS_FINISHED, "handlePlayerInput should return GAME_IS_FINISHED");
}

MU_TEST(test_handle_player_input_move) {
	mu_assert(handlePlayerInput(MOVE_WEST_INPUT, &player) == MOVE_WEST_INPUT, "handlePlayerInput should return MOVE_WEST_INPUT");
}

MU_TEST(test_handle_player_input_random) {
	mu_assert(handlePlayerInput(RANDOM_INPUT, &player) == GAME_IS_RUNNING, "handlePlayerInput should return GAME_IS_RUNNING");
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_save_game);
    MU_RUN_TEST(test_handle_player_input_exit);
	MU_RUN_TEST(test_handle_player_input_move);
	MU_RUN_TEST(test_handle_player_input_random);

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}