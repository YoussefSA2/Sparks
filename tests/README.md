# Tests

The tests are written using the [MinUnit](https://github.com/siu/minunit).

## How to write tests

This is a minimal test suite written with minunit:

```c
/* add.c */

int add(int a, int b) {
    return a + b;
}
```

```c
#include "./include/minunit.h"
#include "../src/add.h"

int a = 1;
int b = 2;

void test_setup(void) {
    a = 1;
    b = 2;
}

MU_TEST(test_add) {
	mu_check(add(a, b) == 3);
    mu_check(add(a, b) != 4);
}


MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test_add);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
```

The idea is to write a function which verifies that your fonction has the right output given a set of inputs.

For example, if you have a function which adds two numbers, you can write a test which verifies that `add(1, 2) == 3`.

Ideally, all functions should be tested. 

The tests are located in the `tests/` directory and are named `test_*.c`.

Please separate the tests in different files, one file per structure (for example `test_map.c` for `Map.c`).

## How to run the tests

```bash
make run-tests
```
