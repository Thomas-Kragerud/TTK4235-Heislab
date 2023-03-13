/**
 * @file main.c
 * @brief The main file of the project, the state machine is run from here.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "timer.h"
#include "fsm.h"

int main(){
    elevio_init();
    order_initialize();

    while(1){

        fsm_run();
        
    }
    return 0;
}
