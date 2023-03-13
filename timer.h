/**
* @file 
* @brief Module contains the functions needed for taking time within a while loop
*
*/

#include <time.h>

/**
* @brief Starts a timer when called, by giving @p time_counter the value of current time.
* @param restart if 1. Otherwise continue counting until @p time_counter is set to -1 by the timer_times_up function
*
*/
void timer_start(int restart);

/**
* @brief Creat a @p time_checker every time its called and return 1 when
* the differance between the @p time_checker and @p time_counter is greater than @p seconds
* @param seconds, the number of seconds before it returns 1
* @return 0 if time is not up, and 1 if time is up
*
*/
int timer_times_up(double seconds);