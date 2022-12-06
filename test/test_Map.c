
#include "./include/minunit.h"
#include "../src/include/Map.h"

static int mapSize = 10;
int **map = NULL;

void test_setup(void) {
	mapSize = 10;
    map = generateMap(mapSize);

}

void test_teardown(void) {
	/* Nothing */
}

MU_TEST(test_generate_map) {
    mu_assert(map != NULL, "map should not be NULL");

    for(int i=0; i < mapSize; ++i)
    {   
        for(int j=0; j < mapSize; ++j)
        {
            mu_assert(map[i][j] == TREE || map[i][j] == OBSTACLE || map[i][j] == FOOD || map[i][j] == EXIT, "map content should be TREE or OBSTACLE or FOOD or EXIT");
        }
    }
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_generate_map);

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}