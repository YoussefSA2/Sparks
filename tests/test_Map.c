#include "./include/minunit.h"
#include "../src/Map.h"

static int map_size = 10;
int **map = NULL;

void test_setup(void) {
	map_size = 10;
    map = generateMap(map_size, map_size);

}

void test_teardown(void) {
	/* Nothing */
}

MU_TEST(test_generate_map) {
    mu_assert(map != NULL, "map should not be NULL");

    for(int i=0; i < map_size; ++i)
    {   
        for(int j=0; j < map_size; ++j)
        {
            mu_assert(map[i][j] == 0 || map[i][j] == 1, "map content should be 0 or 1");
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