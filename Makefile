FLAGS= -Wall -Wextra -pedantic

all: main

clean: 
	rm -f game

compile-game:
	gcc $(FLAGS) -o game src/main.c

run-game: game
	./game