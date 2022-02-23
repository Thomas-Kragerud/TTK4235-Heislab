#include "fsm.h"


state current_state = INIT;

direction current_direction = DIRECTION_DOWN;

direction previous_direction = DIRECTION_DOWN;

position current_position; //kan vær (-1)

position newest_floor_position; //kan bare være (0,..,3)

position previous_floor_position; // kan bare være (0, .., 3)

movement movement_room;

position next_stop;




void fsm_init(void) {
    if(current_position != first) {
            elevio_motorDirection(DIRN_DOWN);
        } else {
            elevio_motorDirection(DIRN_STOP);
            current_direction = DIRECTION_UP; //trenger vi denne her?
            movement_room.start = unknown;
            //movement_room.newest_floor_position
        }
}

//*********************************************************************
//alt som har med movement room å gjøre 








//*********************************************************************//

// har ikke sett på imp
void fsm_update_floor_position(){
    current_position = elevio_floorSensor();
    if (current_position != -1) {
        previous_floor_position = newest_floor_position;
        newest_floor_position = current_position;
    }
}


void fsm_update_light(){
    elevio_floorIndicator(newest_floor_position);
}

//[Pult] har ikke sett på imp



//[pult] har ikke sett på imp
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




//Helper functions implementation 
direction fsm_find_direction(position stop, position start){
    if(stop - start > 0){
        return DIRECTION_UP;
    } else { //in correct floor, send to door open
            //function move in directon 
            //ceck for updates if movement room
            //Shrink movement room 

        return DIRECTION_DOWN;
    }
}










//Main run 

void fsm_run(){

    //Updates for every run of loop 
    fsm_update_floor_position(); //updated {current_position, newest_floor_position, previous_floor_position}
    fsm_update_light();

    switch(current_state) 
    {

        case(INIT):
            fsm_init();
            current_state = IDLE;/
            break;

        case(IDLE):

            queue_update_queue();

            print_matrix(queue);

            



            //hvis ikke eksisterer noen Start Stop; Eller vi er på stop;

                //her vi er nå Start, emergancy stop sletter køen men ikke hvor vi er.
                //Siste opp lengst unna Stop
                //fin directon mellom opp og ned
    
                //nermeste stop i riktig retning, floper herifra og i retning der jeg skal

            //hvis eksisterer et bevegelse room.
                //finn nærmeste neste stop og send til neste


            if(que_not_empty()){
                current_state = MOVING;
            }

            break;
        
        case(MOVING):
            queue_update_queue();
            //Hvis vi er der vi skal være(ende stop)
            if (newest_floor_position == next_stop) {
                current_state = DOOR_OPEN;
            }

            //Hvis ikke er bestemt 
            if (current_direction == DIRECTION_TBT) {
                //finn første entry i kø matrise
            } 

            //hvis bestilling over - motsatt retning eller kryss, oppdater next_stop
        
            //Hvis bestilling inni samme retning.-> newest_floor_position har et kryss i kømatrisen eller retning retning samme retning- Kast opp  
            
            

            break;



        case(DOOR_OPEN):

            queue_update_queue();

            //Vente i tre sek. 
            //Slett etasen fra køeen
            //om alt er nice luk døren og kast til idel 
            break;

        case(EMERGENCY_STOP):
            break;
    }

}