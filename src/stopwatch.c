#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include "machine_state.h"
#include "get_time.h"

#define hour 24
#define minute_hour 59
#define second_minute 59

typedef struct {
    struct timespec start_time;
    struct timespec current_time;
    stopwatch_enum machine_state;
    uint16_t accumulated_time_seconds;  
} stopwatch_context;

typedef struct {
    uint16_t milliseconds;
    uint16_t seconds;
    uint16_t minutes;
    uint16_t hours;
} stopwatch;
 
void stopwatch_function (stopwatch_context * current_stopwatch_context, stopwatch * current_stopwatch) {
    current_stopwatch_context -> current_time = get_time();
    //if current_nsec < start_nsec, the ans might be in negative, so we borrow a sec
    if (current_stopwatch_context -> current_time.tv_nsec < current_stopwatch_context -> start_time.tv_nsec){
       current_stopwatch_context -> current_time.tv_nsec += 1000000000;
       current_stopwatch_context -> current_time.tv_sec -=1;
    }
    current_stopwatch -> milliseconds = (current_stopwatch_context -> current_time.tv_nsec - current_stopwatch_context -> start_time.tv_nsec) / 1000000; //1M ns = 1 ms
    uint16_t total_elasped_secs = (current_stopwatch_context -> current_time.tv_sec - current_stopwatch_context -> start_time.tv_sec) + current_stopwatch_context -> accumulated_time_seconds;
    current_stopwatch -> seconds = total_elasped_secs % 60;

    current_stopwatch -> minutes = (total_elasped_secs / 60) % 60; // first div converts it to mins and modulo resets it zero every time factor of 60 is hit else remainder min is returned
    current_stopwatch -> hours = total_elasped_secs / 3600; // secs -> hours
}

void start_time_for_stopwatch (stopwatch_context * current_stopwatch_context) {
    current_stopwatch_context ->start_time = get_time();
}

int main (void) {
   stopwatch_context *now2 = malloc(sizeof(stopwatch_context)); 
   stopwatch *now = malloc(sizeof(stopwatch));
   start_time_for_stopwatch(now2);
   while(true){
        stopwatch_function (now2, now);
        printf("\r %d:%d:%d:%d", now ->hours, now -> minutes, now -> seconds, now -> milliseconds);
        fflush(stdout);
   }
    return 0;
}