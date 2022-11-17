FLAGS= -Wall -Wextra -pedantic

all: run-game

clean: 
	rm -f game

compile-game:
	gcc $(FLAGS) src/*c -o game

run-game: compile-game
	./game