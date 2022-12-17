#include <stdlib.h>
#include "./include/minunit.h"
#include "../src/include/Player.h"
#include "../src/include/Map.h"

Player player;
int **map;

void test_setup(void) {
    map = generateMap(3, EASY);
}

void test_teardown(void) {
    freeMap(map, 3);
}

MU_TEST(test_init_player) {
    player = initPlayer(map);
    mu_assert(areEqual(player.position, (Coordinates){0, 0}), "player.position should be equal to (0,0)");
    mu_assert(player.energy == 100, "player.energy should be 100");
    mu_assert(player.nbRewinds == 6, "player.nbRewinds should be 6");
    mu_assert(player.movesHistory != NULL, "player.movesHistory should not be NULL");
    mu_assert(cvector_size(player.movesHistory) == 1, "player.movesHistory should have a size of 1");
    mu_assert(areEqual(player.movesHistory[0], (Coordinates){0, 0}), "player.movesHistory[0] should be equal to player.position");

}

MU_TEST(test_modify_energy) {
    player = initPlayer(map);
    modifyEnergy(&player, 10);
    mu_assert(player.energy == 110, "player.energy should be 100");
}

MU_TEST(test_move_north) {
    player = initPlayer(map);
    mu_assert(move(&player, MOVE_NORTH_INPUT) == MOVE_NORTH_INPUT, "move should return MOVE_NORTH_INPUT");
    mu_assert(player.position.x == 0, "player.position.x should be 0");
    mu_assert(player.position.y == -1, "player.position.y should be -1");
}

MU_TEST(test_move_north_east) {
    player = initPlayer(map);
    mu_assert(move(&player, MOVE_NORTH_EAST_INPUT) == MOVE_NORTH_EAST_INPUT, "move should return MOVE_NORTH_EAST_INPUT");
    mu_assert(player.position.x == 1, "player.position.x should be 1");
    mu_assert(player.position.y == -1, "player.position.y should be -1");
}

MU_TEST(test_move_east) {
    player = initPlayer(map);
    mu_assert(move(&player, MOVE_EAST_INPUT) == MOVE_EAST_INPUT, "move should return MOVE_EAST_INPUT");
    mu_assert(player.position.x == 1, "player.position.x should be 1");
    mu_assert(player.position.y == 0, "player.position.y should be 0");
}

MU_TEST(test_move_south_east) {
    player = initPlayer(map);
    mu_assert(move(&player, MOVE_SOUTH_EAST_INPUT) == MOVE_SOUTH_EAST_INPUT, "move should return MOVE_SOUTH_EAST_INPUT");
    mu_assert(player.position.x == 1, "player.position.x should be 1");
    mu_assert(player.position.y == 1, "player.position.y should be 1");
}

MU_TEST(test_move_south) {
    player = initPlayer(map);
    mu_assert(move(&player, MOVE_SOUTH_INPUT) == MOVE_SOUTH_INPUT, "move should return MOVE_SOUTH_INPUT");
    mu_assert(player.position.x == 0, "player.position.x should be 0");
    mu_assert(player.position.y == 1, "player.position.y should be 1");
}

MU_TEST(test_move_south_west) {
    player = initPlayer(map);
    mu_assert(move(&player, MOVE_SOUTH_WEST_INPUT) == MOVE_SOUTH_WEST_INPUT, "move should return MOVE_SOUTH_WEST_INPUT");
    mu_assert(player.position.x == -1, "player.position.x should be -1");
    mu_assert(player.position.y == 1, "player.position.y should be 1");
}

MU_TEST(test_move_west) {
    player = initPlayer(map);
    mu_assert(move(&player, MOVE_WEST_INPUT) == MOVE_WEST_INPUT, "move should return MOVE_WEST_INPUT");
    mu_assert(player.position.x == -1, "player.position.x should be -1");
    mu_assert(player.position.y == 0, "player.position.y should be 0");
}

MU_TEST(test_move_north_west) {
    player = initPlayer(map);
    mu_assert(move(&player, MOVE_NORTH_WEST_INPUT) == MOVE_NORTH_WEST_INPUT, "move should return MOVE_NORTH_WEST_INPUT");
    mu_assert(player.position.x == -1, "player.position.x should be -1");
    mu_assert(player.position.y == -1, "player.position.y should be -1");
}

MU_TEST(test_cancel_move_sucess){
    player = initPlayer(map);
    
    // Move 2 times
    move(&player, MOVE_SOUTH_INPUT);
    
    Coordinates swapPosition = (Coordinates){player.position.y, player.position.x};
    cvector_push_back(player.movesHistory, swapPosition);
    
    move(&player, MOVE_SOUTH_INPUT);
    swapPosition = (Coordinates){player.position.y, player.position.x};
    cvector_push_back(player.movesHistory, player.position);
    
    mu_assert(cancelMove(&player) == CANCEL_MOVE_SUCCESS, "cancelMove should return CANCEL_MOVE_SUCCESS");
    mu_assert(areEqual(player.position, (Coordinates){0,1}), "player.position should be (0,1)");
}

MU_TEST(test_cancel_move_no_rewinds_left){
    player = initPlayer(map);
    player.nbRewinds = 0;
    
    move(&player, MOVE_SOUTH_INPUT);
    cvector_push_back(player.movesHistory, player.position);
    mu_assert(cancelMove(&player) == NO_REWINDS_LEFT, "cancelMove should return NO_REWINDS_LEFT");
    mu_assert(areEqual(player.position, (Coordinates){0,1}), "player.position should be (0,1)");

}

MU_TEST(test_cancel_move_no_moves_made){
    player = initPlayer(map);

    mu_assert(cancelMove(&player) == NO_MOVE_TO_CANCEL, "cancelMove should return NO_MOVE_TO_CANCEL");
    mu_assert(areEqual(player.position, (Coordinates){0,0}), "player.position should be (0,0)");
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
    MU_RUN_TEST(test_cancel_move_sucess);
    MU_RUN_TEST(test_cancel_move_no_rewinds_left);
    MU_RUN_TEST(test_cancel_move_no_moves_made);

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}