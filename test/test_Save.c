
#include "./include/minunit.h"
#include "../src/include/Save.h"

Player player;
int **map = NULL;

void test_setup(void) {
    map = generateMap(10, EASY);
	player = initPlayer(map);
}

void test_teardown(void) {
    freeMap(map, 10);
}

MU_TEST(test_save_game) {
    mu_assert(saveGame(&player, map, '1') == PLAYER_SAVED, "saveGame should return PLAYER_SAVED");
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

	saveGame(&player, map, '1');

	//modify infos so we can check that the game correctly loads infos above
	player.energy = 0;
	player.position = (Coordinates) {0,0};
	player.movesHistory = NULL;

	map[1][0] = FOOD;
	map[0][1] = OBSTACLE;
	map[0][2] = TREE;

	loadGame(&player, map, '1');

	mu_assert(player.energy == 50, "player.energy should be 50");
	mu_assert(areEqual(player.position, (Coordinates) {1, 3}), "player.position should be (1,3)");
	mu_assert(areEqual(player.movesHistory[1], (Coordinates) {0,2}), "player.movesHistory[1] should contains (0,2)");
	mu_assert_int_eq(cvector_size(player.movesHistory), 2); //start position + 1 move
	mu_assert_int_eq(map[1][0], TREE);
	mu_assert_int_eq(map[0][1], FOOD);
	mu_assert_int_eq(map[0][2], OBSTACLE);
}

MU_TEST(test_save_on_multiple_save_slots){
	//informations to save
	player.energy = 50;
	player.position = (Coordinates) {1, 3};
	cvector_push_back(player.movesHistory, ((Coordinates) {0,2}));

	map[1][0] = TREE;
	map[0][1] = FOOD;
	map[0][2] = OBSTACLE;

	saveGame(&player, map, '1');
	
	// different infos for different save slot
	player.energy = 100;
	
	saveGame(&player, map, '2');

	//modify infos so we can check that the game correctly loads infos above
	player.energy = 0;
	player.position = (Coordinates) {0,0};
	player.movesHistory = NULL;

	map[1][0] = FOOD;
	map[0][1] = OBSTACLE;
	map[0][2] = TREE;

	loadGame(&player, map, '1');

	mu_assert(player.energy == 50, "player.energy should be 50");
	mu_assert(areEqual(player.position, (Coordinates) {1, 3}), "player.position should be (1,3)");
	mu_assert(areEqual(player.movesHistory[1], (Coordinates) {0,2}), "player.movesHistory[1] should contains (0,2)");
	mu_assert_int_eq(cvector_size(player.movesHistory), 2); //start position + 1 move
	mu_assert_int_eq(map[1][0], TREE);
	mu_assert_int_eq(map[0][1], FOOD);
	mu_assert_int_eq(map[0][2], OBSTACLE);

	loadGame(&player, map, '2');

	mu_assert(player.energy == 100, "player.energy should be 50");
	mu_assert(areEqual(player.position, (Coordinates) {1, 3}), "player.position should be (1,3)");
	mu_assert(areEqual(player.movesHistory[1], (Coordinates) {0,2}), "player.movesHistory[1] should contains (0,2)");
	mu_assert_int_eq(cvector_size(player.movesHistory), 2); //start position + 1 move
	mu_assert_int_eq(map[1][0], TREE);
	mu_assert_int_eq(map[0][1], FOOD);
	mu_assert_int_eq(map[0][2], OBSTACLE);

}


MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_load_game);
    MU_RUN_TEST(test_save_game);
	MU_RUN_TEST(test_save_on_multiple_save_slots);

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}