#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "driver/elevio.h"
#include "queue.h"
#include "util.h"

typedef enum {INIT, IDLE, MOVING, DOOR_OPEN, EMERGENCY_STOP} state;

typedef enum {DIRECTION_DOWN, DIRECTION_UP, DIRECTION_TBT} direction; //Trenger vi TBT

typedef enum {unknown = -1, first = 0, second = 1, third = 2, fourth = 3} position;

typedef struct
{
    position start;
    position stop;
    position next_stop;
    direction movement_dir;

} movement;


extern state current_state;

extern direction current_direction;

extern direction previous_direction;


void fsm_update_movement_room();

void fsm_movement_room_handler();




/**
 * @brief Initilize the elevator to a known state
 * 
 */
void fsm_init(void);

/**
 * @brief Function that updates the last passed floor
 * 
 * 
 * 
 */
void fsm_update_floor_position();

/**
 * @brief Updates floor indicator light at panel
 * 
 */
void fsm_update_light();

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


/**
 * @brief Runs the whole elevator
 * 
 */
void fsm_run();


//Helper functions

direction fsm_find_direction(position stop, position start);