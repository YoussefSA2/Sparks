#include <stdlib.h>
#include "./include/minunit.h"
#include "../src/include/Player.h"

Player player;

void test_setup(void) {
}

void test_teardown(void) {
	/* Nothing */
}

MU_TEST(test_init_player) {
    player = initPlayer();
    mu_assert(player.position.x == 0, "player.position.x should be 0");
    mu_assert(player.position.y == 0, "player.position.y should be 0");
    mu_assert(player.energy == 100, "player.energy should be 100");
    mu_assert(player.nbRewinds == 6, "player.nbRewinds should be 6");
}

MU_TEST(test_modify_energy) {
    player = initPlayer();
    modifyEnergy(&player, 10);
    mu_assert(player.energy == 110, "player.energy should be 100");
}

MU_TEST(test_move_north) {
    player = initPlayer();
    mu_assert(move(&player, MOVE_NORTH_INPUT) == MOVE_NORTH_INPUT, "move should return MOVE_NORTH_INPUT");
    mu_assert(player.position.x == 0, "player.position.x should be 0");
    mu_assert(player.position.y == 1, "player.position.y should be 1");
}

MU_TEST(test_move_north_east) {
    player = initPlayer();
    mu_assert(move(&player, MOVE_NORTH_EAST_INPUT) == MOVE_NORTH_EAST_INPUT, "move should return MOVE_NORTH_EAST_INPUT");
    mu_assert(player.position.x == 1, "player.position.x should be 1");
    mu_assert(player.position.y == 1, "player.position.y should be 1");
}

MU_TEST(test_move_east) {
    player = initPlayer();
    mu_assert(move(&player, MOVE_EAST_INPUT) == MOVE_EAST_INPUT, "move should return MOVE_EAST_INPUT");
    mu_assert(player.position.x == 1, "player.position.x should be 1");
    mu_assert(player.position.y == 0, "player.position.y should be 0");
}

MU_TEST(test_move_south_east) {
    player = initPlayer();
    mu_assert(move(&player, MOVE_SOUTH_EAST_INPUT) == MOVE_SOUTH_EAST_INPUT, "move should return MOVE_SOUTH_EAST_INPUT");
    mu_assert(player.position.x == 1, "player.position.x should be 1");
    mu_assert(player.position.y == -1, "player.position.y should be -1");
}

MU_TEST(test_move_south) {
    player = initPlayer();
    mu_assert(move(&player, MOVE_SOUTH_INPUT) == MOVE_SOUTH_INPUT, "move should return MOVE_SOUTH_INPUT");
    mu_assert(player.position.x == 0, "player.position.x should be 0");
    mu_assert(player.position.y == -1, "player.position.y should be -1");
}

MU_TEST(test_move_south_west) {
    player = initPlayer();
    mu_assert(move(&player, MOVE_SOUTH_WEST_INPUT) == MOVE_SOUTH_WEST_INPUT, "move should return MOVE_SOUTH_WEST_INPUT");
    mu_assert(player.position.x == -1, "player.position.x should be -1");
    mu_assert(player.position.y == -1, "player.position.y should be -1");
}

MU_TEST(test_move_west) {
    player = initPlayer();
    mu_assert(move(&player, MOVE_WEST_INPUT) == MOVE_WEST_INPUT, "move should return MOVE_WEST_INPUT");
    mu_assert(player.position.x == -1, "player.position.x should be -1");
    mu_assert(player.position.y == 0, "player.position.y should be 0");
}

MU_TEST(test_move_north_west) {
    player = initPlayer();
    mu_assert(move(&player, MOVE_NORTH_WEST_INPUT) == MOVE_NORTH_WEST_INPUT, "move should return MOVE_NORTH_WEST_INPUT");
    mu_assert(player.position.x == -1, "player.position.x should be -1");
    mu_assert(player.position.y == 1, "player.position.y should be 1");
}


MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_init_player);
    MU_RUN_TEST(test_modify_energy);
    MU_RUN_TEST(test_move_north);
    MU_RUN_TEST(test_move_north_east);
    MU_RUN_TEST(test_move_east);
    MU_RUN_TEST(test_move_south_east);
    MU_RUN_TEST(test_move_south);
    MU_RUN_TEST(test_move_south_west);
    MU_RUN_TEST(test_move_west);
    MU_RUN_TEST(test_move_north_west);

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}