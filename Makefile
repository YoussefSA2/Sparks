FLAGS= -Wall -Wextra -pedantic

MAIN= src/main.c
SOURCES_WITOUT_MAIN= $(filter-out $(MAIN), $(wildcard src/*.c))

all: run-game

clean: 
	rm -f game tests_*

compile-game:
	gcc $(FLAGS) src/*.c -o game

compile-tests:
	gcc $(FLAGS) -lrt -lm test/test_Game.c $(SOURCES_WITOUT_MAIN) -o tests_game
	gcc $(FLAGS) -lrt -lm test/test_Map.c $(SOURCES_WITOUT_MAIN) -o tests_map
	gcc $(FLAGS) -lrt -lm test/test_Player.c $(SOURCES_WITOUT_MAIN) -o tests_player

run-game: compile-game
	./game

run-tests: compile-tests
	./tests_game
	./tests_map
	./tests_player