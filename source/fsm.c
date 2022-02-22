#include "fsm.h"


state current_state = INIT;

direction current_direction = DIRECTION_DOWN;

direction previous_direction = DIRECTION_DOWN;

position current_position;

movement movement_room;




void fsm_init(void) {
    if(current_position != 0) {
            elevio_motorDirection(DIRN_DOWN);
        } else {
            elevio_motorDirection(DIRN_STOP);
            current_direction = DIRECTION_UP;
            current_state = IDLE;
        }
}


void fsm_update_movement_room(){
    for(int f = 0; f < NUMBER_OF_FLOORS; ++f){
        for(int b = 0; b < NUMBER_OF_BUTTONS; ++b){
            if(queue[f][b] != 0){

                //if finds new entry the first time.
                movement_room.stop = f;
                movement_room.next_stop = f;
                movement_room.start = current_position;
            }
        }
    }
}

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
    int next_stop = 5;

    if(current_direction == DIRECTION_UP) {
        for (int i = floor_indicator; i < NUMBER_OF_FLOORS; ++i) {
            for (int j = 0; j < NUMBER_OF_BUTTONS; ++j) {
                if ((queue[i][j] == 1) && (i > floor_indicator) && i != next_stop && (abs(i-floor_indicator) < abs(next_stop-floor_indicator))) {
                    next_stop = i;
                }
            }
        }
    }

    if(current_direction == DIRECTION_DOWN) {
        for (int i = 0; i < floor_indicator; ++i) {
            for (int j = 0; j < NUMBER_OF_BUTTONS; ++j) {
                if ((queue[i][j] == 1) && (i < floor_indicator) && i != next_stop && (abs(i-floor_indicator) < abs(next_stop-floor_indicator))) {
                    next_stop = i;
                }
            }
        }
    }

    return next_stop;
}

void fsm_go_to(int next_stop, int floor_indicator) {
    if (next_stop != 5) {
        if (next_stop > floor_indicator) {
            elevio_motorDirection(DIRN_UP);
        }
        if (next_stop < floor_indicator) {
            elevio_motorDirection(DIRN_DOWN);
        }
    } else {
        elevio_motorDirection(DIRN_STOP);
    }
}


void fsm_clear_orders_on_floor(int floor) {
    for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        queue[floor][i] = 0;
    } 
}


void fsm_run(){

    //Updates for every run of loop 
    current_position = elevio_floorSensor();
    fsm_update_light(fsm_get_floor_indicator(current_position));

    switch(current_state) 
    {

        case(INIT):
            fsm_init();
            break;

        case(IDLE):
            queue_update_queue();
            print_matrix(queue);
            if(que_not_empty()){
                current_state = MOVING;
            }
            /**

            int floor_indicator = fsm_get_floor_indicator(current_position);
            int next_stop = fsm_get_next_stop(floor_indicator);

            fsm_go_to(next_stop, floor_indicator);

            if (next_stop == floor_indicator) {
                elevio_motorDirection(DIRN_STOP);
                fsm_clear_orders_on_floor(next_stop);
                current_state = DOOR_OPEN;
            }
            printf("%d", next_stop);
            printf("%d\n", floor_indicator);
            **/

            break;
        
        case(MOVING):
            int floor_indicator = fsm_get_floor_indicator(current_position);
            int next_stop = fsm_get_next_stop(floor_indicator);

            fsm_go_to(next_stop, floor_indicator);

            if (next_stop == floor_indicator) {
                elevio_motorDirection(DIRN_STOP);
                fsm_clear_orders_on_floor(next_stop);
                current_state = DOOR_OPEN;
            }
            printf("%d", next_stop);
            printf("%d\n", floor_indicator);

            break;



        case(DOOR_OPEN):
        while(1) {
            int a = 1;
        }
        break;
    }

}