ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname)  
endif

FLAGS= -Wall -Wextra -pedantic
LINUX_TEST_FLAGS= -lrt -lm

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
	if [ "$(detected_OS)" = "Windows" ]; then \
		gcc $(FLAGS) test/test_Game.c $(SOURCES_WITOUT_MAIN) -o tests_Game.exe; \
		gcc $(FLAGS) test/test_Map.c $(SOURCES_WITOUT_MAIN) -o tests_Map.exe; \
		gcc $(FLAGS) test/test_Player.c $(SOURCES_WITOUT_MAIN) -o tests_Player.exe; \
		gcc $(FLAGS) test/test_Path.c $(SOURCES_WITOUT_MAIN) -o tests_Path.exe; \
		gcc $(FLAGS) test/test_CoordinatesQueue.c $(SOURCES_WITOUT_MAIN) -o tests_Coordinates_Queue.exe; \
	else \
		gcc $(FLAGS) $(LINUX_TEST_FLAGS) test/test_Game.c $(SOURCES_WITOUT_MAIN) -o tests_game; \
		gcc $(FLAGS) $(LINUX_TEST_FLAGS) test/test_Map.c $(SOURCES_WITOUT_MAIN) -o tests_map; \
		gcc $(FLAGS) $(LINUX_TEST_FLAGS) test/test_Player.c $(SOURCES_WITOUT_MAIN) -o tests_player; \
		gcc $(FLAGS) $(LINUX_TEST_FLAGS) test/test_Path.c $(SOURCES_WITOUT_MAIN) -o tests_path; \
		gcc $(FLAGS) $(LINUX_TEST_FLAGS) test/test_CoordinatesQueue.c $(SOURCES_WITOUT_MAIN) -o tests_coordinates_queue; \
	fi

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