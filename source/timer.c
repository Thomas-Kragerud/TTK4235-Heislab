#include "timer.h"



static time_t time_counter = -1;
static time_t time_checker = -1;

void timer_start() {
    if(time_counter == -1){
        time_counter = time(NULL);
    }
}

int timer_times_up(double seconds) {
    time_checker = time(NULL);
    if(time_checker == -1){
        time_checker = time(NULL);
    }
    if (seconds < difftime(time_checker, time_counter)) {
        time_counter = -1;
        time_checker = -1;
        return 1;
    }
    return 0;
}

void timer_sec(double seconds){
    struct timespec t;
    t.tv_sec = seconds;
    t.tv_nsec = 0;
    nanosleep(&t, NULL);
}



