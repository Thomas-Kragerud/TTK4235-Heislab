/**
 * @file fsm.c
 * @brief Implements the runtime logic
 * 
 */

#include "fsm.h"

state current_state = INIT;

direction current_direction = DIRECTION_TBD;

direction previous_direction = DIRECTION_TBD;

position current_position;

position newest_floor_position;

position last_stop;



int fsm_init(void) {
    if (current_position != first) {
        elevio_motorDirection(DIRN_DOWN);
        return 0;
    } else {
        elevio_motorDirection(DIRN_STOP);
        return 1;
    }
}

void fsm_update_floor_position() {
    current_position = elevio_floorSensor();
    if (current_position != -1) {
        newest_floor_position = current_position;
    }
}

void fsm_update_light() {
    elevio_floorIndicator(newest_floor_position);
    for (int f = 0; f < NUMBER_OF_FLOORS; ++f) {
        for (int b = 0; b < NUMBER_OF_BUTTONS; ++b) {
            if (orders[f][b]) {
                elevio_buttonLamp(f, b, 1);
            } else {
                elevio_buttonLamp(f, b, 0);
            }
        }
    }
}

void fsm_go_to(int floor) {
    if (floor > newest_floor_position) {
        elevio_motorDirection(DIRN_UP);
    }
    if (floor < newest_floor_position) {
        elevio_motorDirection(DIRN_DOWN);
    }
    //These two if-statements are made specifically for the case of emergency stop between two floors.
    if (floor == newest_floor_position && current_position == -1 && previous_direction == DIRECTION_UP) {
        elevio_motorDirection(DIRN_DOWN);
    }
    if (floor == newest_floor_position && current_position == -1 && previous_direction == DIRECTION_DOWN) {
        elevio_motorDirection(DIRN_UP);
    }
}

void fsm_find_direction() {
    last_stop = order_find_entry();
    if (last_stop > newest_floor_position) {
        current_direction = DIRECTION_UP;
    }
    if (last_stop < newest_floor_position) {
        current_direction = DIRECTION_DOWN;
    }
    if (last_stop == newest_floor_position) {
        current_direction = DIRECTION_TBD;
    }
    //These two if-statements are made specifically for the case of emergency stop between two floors.
    if (last_stop == newest_floor_position && current_position == -1 && previous_direction == DIRECTION_UP) {
        current_direction = DIRECTION_DOWN;
    }
    if (last_stop == newest_floor_position && current_position == -1 && previous_direction == DIRECTION_DOWN) {
        current_direction = DIRECTION_UP;
    }
}

void fsm_search_beyond_last_stop() {
    //If the current direction is up we loop through the floors above the last_stop and look for cabinbtn above us
    if (current_direction == DIRECTION_UP) {
        for (int f = last_stop + 1; f < NUMBER_OF_FLOORS; ++f) {
            if (orders[f][1] == 1) { // found a downbtn
                last_stop = f;
            }
            if (orders[f][2] == 1) { // found a cabinbtn
                last_stop = f;
            }
        }
        //Direction down, loop fra last_stop and down,looking for upbtn and hallbtn
        if (current_direction == DIRECTION_DOWN) {
            for (int f = 0; f < last_stop; ++f) {
                if (orders[f][0] == 1) { // found a upbtn
                    last_stop = f;
                }

                if (orders[f][2] == 1) { // found a cabinbtn
                    last_stop = f;
                }
            }
        }
    }
}

int fsm_valid_stop() {
    if ((orders[newest_floor_position][current_direction] == 1 || orders[newest_floor_position][2] == 1) &&
        current_position != -1) {
        return 1;
    }
    return 0;
}

void fsm_run() {
    //Updates regardless of current state
    fsm_update_floor_position(); // updates: current_position, newest_floor_position
    fsm_update_light();

    switch (current_state) {

        case (INIT):
            if (fsm_init()) { current_state = IDLE; }
            break;

        case (IDLE):
            order_update_orders();
            if (elevio_stopButton()) { current_state = EMERGENCY_STOP; }
            if (order_find_entry() != -1) { current_state = MOVING; }
            break;

        case (MOVING):
            order_update_orders();
            // if direction is not determined, finds direction
            if (current_direction == DIRECTION_TBD) {fsm_find_direction();}
            // if we are at the final stop in this direction
            if (newest_floor_position == last_stop && current_position != -1) {  //lagt til en && av oskar
                current_state = DOOR_OPEN;
                current_direction = DIRECTION_TBD;
            }
            // Looks for orders beyond the last_stop -> in opposite direction or in elevator floor orders.
            fsm_search_beyond_last_stop();
            // Checks if current position is a valid stop -> order in same direction or a cabin order.
            if (fsm_valid_stop()) { current_state = DOOR_OPEN; }
            fsm_go_to(last_stop);
            if (elevio_stopButton()) {
                current_state = EMERGENCY_STOP;
                previous_direction = current_direction;
                current_direction = DIRECTION_TBD;
            }
            break;

        case (DOOR_OPEN):
            order_update_orders();
            if (elevio_stopButton()) { current_state = EMERGENCY_STOP; }
            
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
            order_clear_row(newest_floor_position);

            timer_start(0);
            if (elevio_obstruction()) { timer_start(1); } //restarts timer if obstruction is active
            if (timer_times_up(2) && !elevio_obstruction()){//counts 2, 1, 0 , finished
                current_state = IDLE;
                elevio_doorOpenLamp(0);
            }
            break;

        case (EMERGENCY_STOP):
            elevio_motorDirection(DIRN_STOP);
            elevio_stopLamp(1);
            order_initialize();

            if (current_position == newest_floor_position) //only true when the elevator is located in a floor
            {
                if (!elevio_stopButton()) {
                    elevio_stopLamp(0);
                    timer_start(1);
                    current_state = DOOR_OPEN;
                } else {
                    elevio_doorOpenLamp(1);
                }

            } else {
                if (!elevio_stopButton()) {
                    elevio_stopLamp(0);
                    current_state = IDLE;
                }
            }
            break;
    }
}
