#include "fsm.h"

state current_state = INIT;

direction current_direction = DIRECTION_TBT;

direction previous_direction = DIRECTION_TBT;

position current_position; // kan vær (-1)

position newest_floor_position; // kan bare være (0,..,3)

position previous_floor_position; // kan bare være (0, .., 3)

movement movement_room;

position next_stop;

int off = 0;

int fsm_init(void)
{
    if (current_position != first)
    {
        elevio_motorDirection(DIRN_DOWN);
        return 0;
    }
    else
    {
        elevio_motorDirection(DIRN_STOP);
        return 1;
    }
}

//*********************************************************************
// alt som har med movement room å gjøre

//*********************************************************************//


void fsm_update_floor_position()
{
    current_position = elevio_floorSensor();
    if (current_position != -1)
    {
        previous_floor_position = newest_floor_position;
        newest_floor_position = current_position;
    }
}

void fsm_update_light()
{
    elevio_floorIndicator(newest_floor_position);
}


void fsm_go_to(int next_stop)
{
    if (next_stop > newest_floor_position)
    {
        elevio_motorDirection(DIRN_UP);
    }
    if (next_stop < newest_floor_position)
    {
        elevio_motorDirection(DIRN_DOWN);
    }

    //LAGT til av oskar for å løse problem 1
    if (next_stop == newest_floor_position && current_position == -1 && previous_direction == DIRECTION_UP) {
        elevio_motorDirection(DIRN_DOWN);
        current_direction = DIRECTION_DOWN;
        next_stop = newest_floor_position + 1;
    }
    if (next_stop == newest_floor_position && current_position == -1 && previous_direction == DIRECTION_DOWN) {
        elevio_motorDirection(DIRN_UP);
        current_direction = DIRECTION_UP;
        next_stop = newest_floor_position - 1;
    }

}

//finner retningen 
void fsm_find_directon()
{
    next_stop = queue_find_entry();
    if (next_stop > newest_floor_position)
    {
        current_direction = DIRECTION_UP;
    }
    if (next_stop < newest_floor_position) 
    {
        current_direction = DIRECTION_DOWN;
    }
    if (next_stop == newest_floor_position)
    {
        current_direction = DIRECTION_TBT;
    }
}

void fsm_search_beyond_next_stop()
{
    // hvis direction oppover, lop fra next_stop  og oppver, leter etter nedover-pil og kryss
    if (current_direction == DIRECTION_UP)
    {
        for (int f = next_stop + 1; f < NUMBER_OF_FLOORS; ++f)
        {

            if (queue[f][1] == 1)
            { // funnet en down
                next_stop = f;
            }
            if (queue[f][2] == 1)
            { // funnet en kryss
                next_stop = f;
            }
        }

        // hvis direction nedover, loop fra next_stop og nedover, leter etter oppover-pil og kryss

        if (current_direction == DIRECTION_DOWN)
        {
            for (int f = 0; f < next_stop; ++f)
            {
                if (queue[f][0] == 1)
                { // funnet en up
                    next_stop = f;
                }

                if (queue[f][2] == 1)
                { // funnet en kryss
                    next_stop = f;
                }
            }
        }
    }
}

int fsm_valid_stop()
{
    if ((queue[newest_floor_position][current_direction] == 1 || queue[newest_floor_position][2] == 1) && current_position != -1)
    {
        return 1;
    }
    return 0;
}

// Main run fsm_search_beyond_next_stop


void fsm_run()
{
    

    // Updates for every run of loop
    fsm_update_floor_position(); // updated {current_position, newest_floor_position, previous_floor_position}
    fsm_update_light();
    //printf("Current newest flore: %d\n",newest_floor_position);

    switch (current_state)
    {


    case (INIT):
        if(fsm_init()){
            current_state = IDLE;
            
        }
        
        break;

    case (IDLE):
        queue_update_queue();
        if(elevio_stopButton()){current_state = EMERGENCY_STOP;} //skrive om den her til en smud funksjon, void funksjon siden kalles ofte

        print_matrix(queue);

        if (queue_not_empty())
        {
            current_state = MOVING;
        }

        break;

    case (MOVING):

        queue_update_queue();
        // Hvis ikke er bestemt
        if (current_direction == DIRECTION_TBT)
        {
            fsm_find_directon(); // gir også "første next_stop"
        }

        // Hvis vi er der vi skal være(ende stop) (et ende stelevio_stopButtonopp, vurdering å sette direction til Undetirmand)
        
        if (newest_floor_position == next_stop && current_position != -1) //lagt til en && av oskar
        {
            current_state = DOOR_OPEN;
            current_direction = DIRECTION_TBT;
        }

        // hvis bestilling over - motsatt retning eller kryss, oppdater next_stop
        fsm_search_beyond_next_stop();

        // Hvis bestilling inni samme retning.-> newest_floor_position har et kryss i kømatrisen eller retning retning samme retning- Kast opp

        if (fsm_valid_stop())
        {
            current_state = DOOR_OPEN;
        }

        fsm_go_to(next_stop);

        if(elevio_stopButton()){
            current_state = EMERGENCY_STOP;
            previous_direction = current_direction;
            current_direction = DIRECTION_TBT;}

        break;

    case (DOOR_OPEN):
        queue_update_queue();
        if(elevio_stopButton()){current_state = EMERGENCY_STOP;}
        elevio_motorDirection(DIRN_STOP);
        elevio_doorOpenLamp(1);
        printf("Door open\n");
        queue_clear_row(newest_floor_position);

        timer_start(0);
        if(elevio_obstruction()){timer_start(1);} //restarter timer hvis obstruction knappen er trykket

        //Denne funker ikke helt som den skal -oskar
        if(timer_times_up(2) && !elevio_obstruction()){ //timer_times_up(3) bruker 4 sekunder..
            current_state = IDLE;
            elevio_doorOpenLamp(0);
        }

        
    
        //timer_sec(3);//denne lytter ikke mens, eller hvis jeg leter i main?
        
        

        // Vente i tre sek.
        // Slett etasen fra køeen
        // om alt er nice luk døren og kast til idel
        break;
    
    case(EMERGENCY_STOP):
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        queue_clear_all();


        //endret av Oskar 
        if(current_position == newest_floor_position)//only true when the elevator is located in a floor
        {
            if(!elevio_stopButton()) {
                elevio_stopLamp(0);
                current_state = DOOR_OPEN;
            } else {
                printf("Door open\n");
                elevio_doorOpenLamp(1);
            }      //Eneste som suger er at stoppknappen dimmer...
        } else{


            if(!elevio_stopButton()) {
                elevio_stopLamp(0);
                current_state = IDLE;
            }
        }

        if (elevio_stopButton()) {
            timer_start(0);
            if (timer_times_up(5)) {
                current_state = OFF;
            }
        }

        break;

    case(OFF):

        elevio_doorOpenLamp(0);
        elevio_floorIndicator(0);
        elevio_stopLamp(0);
        off = 1;

        break;


    }

    
}


//Problems::

//1 Etter stopp mellom to etasjer vil ikke heisen registrere trykk på etasjen den akkurat var i
//2 Ved nødstopp i etasje dimmer stoppknapp lyset veldig pga loopen
