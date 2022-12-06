
#include "./include/minunit.h"
#include "../src/include/Map.h"
#include "../src/include/Path.h"
#include "../src/include/Player.h"

static int mapSize;
static int** map = NULL;
static int** mapWithUnreachableExit = NULL;

void test_setup(void) {
	mapSize = 3;
    
    //allocate memory for the map
    map = malloc(sizeof(int*) * mapSize);
    mapWithUnreachableExit = malloc(sizeof(int*) * mapSize);
    for (int i = 0; i < mapSize; i++) {
        map[i] = malloc(sizeof(int) * mapSize);
        mapWithUnreachableExit[i] = malloc(sizeof(int) * mapSize);
    }

    //initialize the map
    map[0][0] = TREE;
    map[0][1] = TREE;
    map[0][2] = TREE;
    map[1][0] = TREE;
    map[1][1] = OBSTACLE;
    map[1][2] = TREE;
    map[2][0] = TREE;
    map[2][1] = TREE;
    map[2][2] = TREE;

    mapWithUnreachableExit[0][0] = TREE;
    mapWithUnreachableExit[0][1] = OBSTACLE;
    mapWithUnreachableExit[0][2] = TREE;
    mapWithUnreachableExit[1][0] = TREE;
    mapWithUnreachableExit[1][1] = OBSTACLE;
    mapWithUnreachableExit[1][2] = TREE;
    mapWithUnreachableExit[2][0] = TREE;
    mapWithUnreachableExit[2][1] = OBSTACLE;
    mapWithUnreachableExit[2][2] = TREE;
}

void test_teardown(void) {
    freeMap(map, mapSize);
}

MU_TEST(test_get_shortest_path_to_exit){
   cvector_vector_type(Coordinates) shortestPath = getShortestPathToExit(map, mapSize);

   Coordinates exitPosition = {mapSize - 1, mapSize - 1};
   
    mu_check(areEqual(shortestPath[0], (Coordinates) {0, 0}));
    mu_check(areEqual(shortestPath[1], (Coordinates) {1, 0}));
    mu_check(areEqual(shortestPath[2], (Coordinates) {2, 1}));
    mu_check(areEqual(shortestPath[3], exitPosition));
}

MU_TEST(test_get_shortest_path_to_exit_unreachable_exit){

    cvector_vector_type(Coordinates) shortestPath = getShortestPathToExit(mapWithUnreachableExit, mapSize);

    mu_check(shortestPath == NULL);
}


MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_get_shortest_path_to_exit);
    MU_RUN_TEST(test_get_shortest_path_to_exit_unreachable_exit);

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}