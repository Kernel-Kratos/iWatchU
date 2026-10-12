#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <time.h>
#include <stdint.h>
#include "machine_state.h"

typedef struct {
    struct timespec start_time;
    struct timespec current_time;
    stopwatch_enum machine_state;
    struct timespec accumulated_time;  
} stopwatch_context;

typedef struct {
    uint16_t milliseconds;
    uint16_t seconds;
    uint16_t minutes;
    uint16_t hours;
} stopwatch;

void stopwatch_function (stopwatch_context * current_stopwatch_context, stopwatch * current_stopwatch);

void start_time_for_stopwatch (stopwatch_context * current_stopwatch_context);

void pause_stopwatch (stopwatch_context *current_stopwatch_context);

#endif