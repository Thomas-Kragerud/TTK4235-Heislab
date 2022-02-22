#include "queue.h"
#include <stdio.h>
#include <stdlib.h>



int queue[NUMBER_OF_FLOORS][NUMBER_OF_BUTTONS];


void queue_initialize_queue() {
    for(int i = 0; i < NUMBER_OF_FLOORS; ++i) {
        for(int j = 0; j < NUMBER_OF_BUTTONS; ++j) {
            queue[i][j] = 0;
        }
    }
}

void queue_update_queue() {
    for(int f = 0; f < NUMBER_OF_FLOORS; ++f) {
        for(int b = 0; b < NUMBER_OF_BUTTONS; ++b) {
            int btnPressed = elevio_callButton(f,b);
            queue[f][b] = btnPressed;
        }
    }
}
