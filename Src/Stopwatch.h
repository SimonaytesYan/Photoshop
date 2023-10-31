#ifndef SYM_STOPWATCH
#define SYM_STOPWATCH
#include <sys/time.h>
#include <ctime>

#define INIT_TIMER()              \
    clock_t startTime, endTime;

#define RESTART_TIMER()             \
        startTime = std::clock();

#define STOP_TIMER()              \
        endTime   = std::clock();

#define GET_TIMER_SECONDS()       \
    (((double)endTime - (double)startTime) / CLOCKS_PER_SEC)

#endif