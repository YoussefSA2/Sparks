FLAGS= -Wall -Wextra -pedantic
TEST_FLAGS= -lrt -lm

MAIN= src/main.c
SOURCES_WITOUT_MAIN= $(filter-out $(MAIN), $(wildcard src/*.c))

all: run-game clean

clean: 
	rm -f game tests_* *.exe

compile-game:
	gcc $(FLAGS) src/*.c -o game

compile-game-debug:
	gcc $(FLAGS) -g src/*.c -o game

compile-tests:
	gcc $(FLAGS) $(TEST_FLAGS) test/test_Game.c $(SOURCES_WITOUT_MAIN) -o tests_game; \
	gcc $(FLAGS) $(TEST_FLAGS) test/test_Map.c $(SOURCES_WITOUT_MAIN) -o tests_map; \
	gcc $(FLAGS) $(TEST_FLAGS) test/test_Player.c $(SOURCES_WITOUT_MAIN) -o tests_player; \
	gcc $(FLAGS) $(TEST_FLAGS) test/test_Path.c $(SOURCES_WITOUT_MAIN) -o tests_path; \
	gcc $(FLAGS) $(TEST_FLAGS) test/test_CoordinatesQueue.c $(SOURCES_WITOUT_MAIN) -o tests_coordinates_queue; \

run-game: compile-game
	./game

run-tests: compile-tests
	./tests_game
	./tests_map
	./tests_player
	./tests_path
	./tests_coordinates_queue

run-debug: compile-game-debug
	gdb game