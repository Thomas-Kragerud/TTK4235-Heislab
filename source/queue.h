#include "fsm.h"


#define NUMBER_OF_FLOORS 4
#define NUMBER_OF_BUTTONS 3



extern int queue[NUMBER_OF_FLOORS][NUMBER_OF_BUTTONS];

void queue_initialize_queue();

void queue_update_queue();

int que_not_empty();

void queue_clear_row(int row);

void queue_clear_all();
