/**
 * @file timer.c
 * @brief Implements the timer.
 * 
 */

#include "timer.h"

static time_t time_counter = -1;
static time_t time_checker = -1;

void timer_start(int restart) {
    if(time_counter == -1 || restart){
        time_counter = time(NULL);
    }
}

int timer_times_up(double seconds) {
    time_checker = time(NULL);
    if (seconds < difftime(time_checker, time_counter)) {
        time_counter = -1;
        return 1;
    }
    return 0;
}


