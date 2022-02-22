#include "fsm.h"


state current_state = INIT;

direction current_direction = DIRECTION_DOWN;

direction previous_direction = DIRECTION_DOWN;

position current_position;


int fsm_get_floor_indicator(int current_position) {
    int floor_indicator = 0;
    if (current_position != -1 && current_position != floor_indicator) {
        floor_indicator = current_position;
    }
    return floor_indicator;
}

void fsm_update_light(int floor_indicator){
    elevio_floorIndicator(floor_indicator);
}

int fsm_get_next_stop(int floor_indicator){
    int next_stop;
    if(current_direction == DIRECTION_UP) {
        for (int i = floor_indicator; i < NUMBER_OF_FLOORS; ++i) {
            for (int j = 0; j < NUMBER_OF_BUTTONS; ++j) {
                if (queue[i][j] == 1 && i > floor_indicator && (abs(i-floor_indicator) < (next_stop-floor_indicator))) {
                    next_stop = i;
                }
            }
        }
    }

    if(current_direction == DIRECTION_DOWN) {
        for (int i = 0; i < floor_indicator; ++i) {
            for (int j = 0; j < NUMBER_OF_BUTTONS; ++j) {
                if (queue[i][j] == 1 && i < floor_indicator && (abs(i-floor_indicator) < (next_stop-floor_indicator))) {
                    next_stop = i;
                }
            }
        }
    }

    return next_stop;
}

void fsm_go_to(int next_stop, int floor_indicator) {
    if (next_stop > floor_indicator) {
        elevio_motorDirection(DIRN_UP);
    } else {
        elevio_motorDirection(DIRN_STOP);
    }
}



void fsm_run(){

    current_position = elevio_floorSensor();
    fsm_update_light(fsm_get_floor_indicator(current_position));

    queue_initialize_queue();

    switch(current_state) 
    {
        case(INIT):
        if(current_position != first) {
            elevio_motorDirection(DIRN_DOWN);
        } else {
            elevio_motorDirection(DIRN_STOP);
            current_state = IDLE;
            current_direction = DIRECTION_UP;
        }

        
        case(IDLE):
        queue_update_queue();
        int floor_indicator = fsm_get_floor_indicator(current_position);
        fsm_go_to(fsm_get_next_stop(floor_indicator), floor_indicator);
    }

}