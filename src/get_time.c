#include <stdio.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64) 
    #include <windows.h>
    #define OS_NAME "WINDOWS"

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
