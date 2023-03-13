/**
 * @file 
 * @brief Implements the runtime logic that drives the elevator.
 * The function fsm_run() is the actual state machine.
 * 
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "driver/elevio.h"
#include "order.h"
#include "timer.h"

typedef enum {INIT, IDLE, MOVING, DOOR_OPEN, EMERGENCY_STOP} state;

typedef enum {DIRECTION_UP, DIRECTION_DOWN, DIRECTION_TBD} direction;

typedef enum {unknown = -1, first = 0, second = 1, third = 2, fourth = 3} position;


state current_state;

direction current_direction;

direction previous_direction;

position current_position;

position newest_floor_position;

position last_stop;

/**
* @brief uses @p newest_floor_position and @p last_stop to determine the direction the elevator will move in
* variables subject to change: @p current_direction
*
*/
void fsm_find_direction();

/**
 * @brief Searches through orders to see if there is a valid
 * variables subject to change: last_stop
 * 
 */
void fsm_search_beyond_last_stop();

/**
 * @brief Checks if @p newest_floor_position is a valid stop on its way to its final destination.
 * A specific floor is said to be valid stop if the @p orders has a floor panel order in the same direction as the elevator or an elevator panel order.
 * @return 1 if valid and 0 if invalid
 * 
 */
int fsm_valid_stop();

/**
 * @brief Initialize the elevator to a known state by moving it to the first floor.
 *
 */
int fsm_init(void);

/**
 * @brief Function that updates all variables needed to determine the elevators current and previous position
 * variables subject to change: @p current_position, @p previous_floor_position, @p newest_floor_position
 *
 */
void fsm_update_floor_position();

/**
 * @brief Updates all lights on the control box.
 * 
 */
void fsm_update_light();

/**
 * @brief Moves elevator in the direction of the input floor.
 * @param floor
 * 
 */
void fsm_go_to(int floor);


/**
 * @brief Finite State Machine that uses the enum "state" to control all operations of the elevator.
 * 
 */
void fsm_run();
