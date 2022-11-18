FLAGS= -Wall -Wextra -pedantic

MAIN= src/main.c
SOURCES_WITOUT_MAIN= $(filter-out $(MAIN), $(wildcard src/*.c))

all: run-game

clean: 
	rm -f *.o

compile-game:
	gcc $(FLAGS) src/*.c -o game.o

compile-tests:
	gcc $(FLAGS) -lrt -lm tests/test_*.c $(SOURCES_WITOUT_MAIN) -o tests.o

run-game: compile-game
	./game

run-tests: compile-tests
	./tests.o