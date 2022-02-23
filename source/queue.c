#include "queue.h"
#include <stdio.h>
#include <stdlib.h>



int queue[NUMBER_OF_FLOORS][NUMBER_OF_BUTTONS];


void queue_initialize_queue() {
    for(int i = 0; i < NUMBER_OF_FLOORS; ++i) {
        for(int j = 0; j < NUMBER_OF_BUTTONS; ++j) {
            queue[i][j] = 0;
            elevio_buttonLamp(i, j, 0);
            
        }
    }
}

void queue_update_queue() {
    for(int f = 0; f < NUMBER_OF_FLOORS; ++f) {
        for(int b = 0; b < NUMBER_OF_BUTTONS; ++b) {
            int btnPressed = elevio_callButton(f,b);//f is floor and b is buttontype [up, down, hb]
            if(btnPressed == 1) {
                queue[f][b] = btnPressed;
                elevio_buttonLamp(f, b, 1);
            }
        }
    }
}



int queue_not_empty(){
    for(int f = 0; f < NUMBER_OF_FLOORS; ++f){
        for(int b = 0; b < NUMBER_OF_BUTTONS; ++b){
            if(queue[f][b] != 0){
                return 1;
            }
        }
    }
    return 0;
}


int queue_find_entry() {
    for(int f = 0; f < NUMBER_OF_FLOORS; ++f){
        for(int b = 0; b < NUMBER_OF_BUTTONS; ++b){
            if(queue[f][b] == 1){
                return f;
            }
        }
    }
    //return 0;
}







//Helper functions implementation 

void queue_clear_row(int floor){
    for(int b = 0; b < NUMBER_OF_BUTTONS; ++b){
        queue[floor][b] = 0;
        elevio_buttonLamp(floor, b, 0);

    }
}


void queue_clear_all(){
    queue_initialize_queue(); // heftig unødvendig :))
}

