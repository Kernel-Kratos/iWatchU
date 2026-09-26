#include <stdio.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64) 
    #include <windows.h>
    #define OS_NAME "WINDOWS"
    struct timespec get_time(void) {
        struct timespec ts;
        LARGE_INTEGER StartingTime, Frequency;
        QueryPerformanceFrequency (&Frequency); // QPF job is to get hardware ticks per_second
        QueryPerformanceCounter (&StartingTime); // QPC job is calculate ticks since sys got on
        // QPF/QPC = secs since sys got on .
        ts.tv_sec = StartingTime.QuadPart / Frequency.QuadPart; //quadpart's type is longlong 
        // QPF % QPC = leftover ticks in a sec * 1B = x B ticks/ QPF = nanoseconds
        ts.tv_nsec = ((StartingTime.QuadPart % Frequency.QuadPart) *  1000000000) / Frequency.QuadPart;  // 1 sec = 1 B nanosec
        return ts;
    }
    
#elif defined(__unix__)
    #include <unistd.h>
    #include <stdlib.h>  
    struct timespec get_time(void) {
        struct timespec ts;
        if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts) == -1) {
            perror("clock_gettime");
            exit(EXIT_FAILURE);
        } 
        return ts;
    }   
#endif
