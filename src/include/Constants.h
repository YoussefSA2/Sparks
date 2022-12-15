#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define MAP_SIZE 10
#define NUMBER_OF_POSITIONS MAP_SIZE * MAP_SIZE

/*
* Game states
*/
#define PLAYER_SAVED -1
#define GAME_IS_RUNNING 0
#define MOVE_SUCCESS 1
#define FOOD_FOUND 2
#define OBSTACLE_HIT 3
#define CANCEL_MOVE_SUCCESS 4
#define NO_REWINDS_LEFT 5
#define NO_MOVE_TO_CANCEL 6
#define PLAYER_WON 1
#define PLAYER_LOST 2

// Launch game states
#define INVALID_LAUNCH_GAME_CHOICE -1
#define GAME_LOAD_FAILED -2
#define GAME_LOAD_SUCCESS 1
#define END_REPLAY 9

/*
* Player inputs
*/

#define EXIT_INPUT 'q'

// Menu inputs
#define NEW_GAME '1'
#define LOAD_GAME '2'
#define REPLAY_GAME '3'

// Direction inputs
#define MOVE_NORTH_INPUT '8'
#define MOVE_NORTH_EAST_INPUT '9'
#define MOVE_EAST_INPUT '6'
#define MOVE_SOUTH_EAST_INPUT '3'
#define MOVE_SOUTH_INPUT '2'
#define MOVE_SOUTH_WEST_INPUT '1'
#define MOVE_WEST_INPUT '4'
#define MOVE_NORTH_WEST_INPUT '7'
#define INVALID_DIRECTION_INPUT '0'
#define CANCEL_MOVE_INPUT 'c'
/*
* Boolean values
*/

#define true 1
#define false 0

// Replay speeds
#define SLOW '1'
#define NORMAL '2'
#define FAST '3'

#endif