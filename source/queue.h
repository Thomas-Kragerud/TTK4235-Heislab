#include "fsm.h"


#define NUMBER_OF_FLOORS 4
#define NUMBER_OF_BUTTONS 3



extern int queue[NUMBER_OF_FLOORS][NUMBER_OF_BUTTONS];

void queue_initialize_queue();

void queue_update_queue();

int queue_not_empty();

int queue_find_entry();

void queue_clear_row(int floor);

void queue_clear_all();
