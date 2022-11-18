#include <stdlib.h>
#include "./include/minunit.h"
#include "../src/include/Game.h"

#define EXIT_INPUT 'q'
#define EXIT_SIGNAL 1
#define RANDOM_INPUT 'r'

#define false 0
#define true 1

void test_setup(void) {
}

void test_teardown(void) {
	/* Nothing */
}

MU_TEST(test_save_game) {
    mu_assert(saveGame() == EXIT_SIGNAL, "saveGame should return EXIT_SIGNAL");
}

MU_TEST(test_handle_player_input) {
    mu_assert(handlePlayerInput(EXIT_INPUT) == EXIT_SIGNAL, "handlePlayerInput should return EXIT_SIGNAL");
	mu_assert(handlePlayerInput(RANDOM_INPUT) == false, "handlePlayerInput should return false");
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_save_game);
    MU_RUN_TEST(test_handle_player_input);

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}