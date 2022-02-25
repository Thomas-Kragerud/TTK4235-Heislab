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
    
    queue_initialize_queue();

    while(1){

        fsm_run();
        if (off) {
            printf("Takk for at du prøvekjørte the intellevator\n");
            break;
        }
        
    }
    return 0;
}
