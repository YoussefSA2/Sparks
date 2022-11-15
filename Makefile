FLAGS= -Wall -Wextra -pedantic

all: run-game

clean: 
	rm -f game

compile-game:
	gcc $(FLAGS) -o game src/main.c

run-game: compile-game
	./game