#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define MAP_SIZE 10

/*
 * Game states
 */
#define PLAYER_SAVED -1
#define GAME_IS_RUNNING 0
#define MOVE_SUCCESS 1
#define FOOD_FOUND 2
#define OBSTACLE_HIT 3
#define PLAYER_WON 1
#define PLAYER_LOST 2

/*
 * Player inputs
 */

#define EXIT_INPUT 'q'
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

#endif