#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "timer.h"
#include "demo_util.h"
#include "fsm.h"



int main(){
    elevio_init();
    time_countdown(3);

    while(1){

        fsm_run();
        
    }

    return 0;
}
