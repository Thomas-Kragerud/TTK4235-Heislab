#include "demo_util.h"

void p() {printf("Du er ikke henta enda\n");}

void time_countdown(int sek){
    for(int i = sek; i >= 0; i--){
        printf("%d\n", i);
        struct timespec t;
        t.tv_sec = 1;
        t.tv_nsec = 0;
        nanosleep(&t, NULL);
    }
}


void thomas_example_program(){
    printf("*** This is an example program made by Thomas ***\n");
    //elevio_init(); bare kalle en gang 

    //levio_motorDirection(DIRN_UP);
    int floor;
    int previois_floor = -2;
    int stop_button;
    int go_to_button = -1;
    MotorDirection dir;
    dir = DIRN_UP;
    elevio_motorDirection(dir);

    //elevio_motorDirection(DIRN_DOWN);

    while(69){
        floor = elevio_floorSensor();
        //go_to_button = elevio_callButton(floor, BUTTON_CAB);
        if(floor != -1 && floor != previois_floor){
            previois_floor = floor;
            printf("floor number %d\n", floor);
            elevio_floorIndicator(floor);
            //printf("Go to button: %d\n", go_to_button);
        }
        if (floor == 0){
            dir = DIRN_UP;
            elevio_motorDirection(dir);
        }
        if (floor == N_FLOORS - 1) {
            dir = DIRN_DOWN;
            elevio_motorDirection(dir);
        }
        //bruker først en if for å se om den er trykket 
        if(elevio_stopButton()){
            timer_start();
            printf("Elevator stoped\n");
            elevio_stopLamp(1);
            //grunnen til at jeg bruker en while og if er at jeg da enkelt kan endre noe på vei ut at if 
            while(elevio_stopButton()){
                elevio_motorDirection(DIRN_STOP);
                if(timer_times_up(3)){printf("Elevator shut down\n"); elevio_stopLamp(0); return;} //hvis timer går over 3 sek retunerer jeg programmet.
            }
            //denne hadde ikke vært mulig med kun en while
            printf("Elvator continues\n");
            elevio_stopLamp(0);
            elevio_motorDirection(dir);
        }


        //neste naturlige steg er å få button in på heispanel til å funke for å klare å styre til enkelt heis.
    }
}

