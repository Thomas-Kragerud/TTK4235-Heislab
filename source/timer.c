#include "timer.h"
#include <time.h>


time_t time_counter;

void timer_start() {
    time_counter = time(NULL);
}

int timer_times_up(double seconds) {
    time_t time_checker = time(NULL);
    if (seconds < difftime(time_checker, time_counter)) {
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



