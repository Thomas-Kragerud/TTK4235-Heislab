#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "driver/elevio.h"
#include "queue.h"

typedef enum {INIT, IDLE, MOVING, DOOR_OPEN, EMERGENCY_STOP} state;

typedef enum {DIRECTION_DOWN, DIRECTION_UP} direction;

typedef enum {first = 0, second = 1, third = 2, fourth = 3} position;

extern state current_state;

extern direction current_direction;

extern direction previous_direction;

/**
 * @brief Function that return the last passed floor
 * 
 * @param current_position Position of elevator (-1 between floors)
 * @return int 
 */
int fsm_get_floor_indicator(int current_position);

/**
 * @brief Updates floor indicator light at panel
 * 
 * @param floor_indicator 
 */
void fsm_update_light(int floor_indicator);

/**
 * @brief Function that calculates the next floor
 * 
 * @param floor_indicator 
 * @return int 
 */
int fsm_get_next_stop(int floor_indicator);

/**
 * @brief Elevator goes to floor and stops
 * 
 * @param next_stop 
 * @param floor_indicator 
 */
void fsm_go_to(int next_stop, int floor_indicator);


void fsm_clear_orders_on_floor(int floor);

/**
 * @brief Runs the whole elevator
 * 
 */
void fsm_run();