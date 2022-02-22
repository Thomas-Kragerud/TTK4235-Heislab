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

int fsm_get_floor_indicator(int current_position);

void fsm_update_light(int floor_indicator);

int fsm_get_next_stop(int floor_indicator);

void fsm_go_to(int next_stop);

void fsm_run();