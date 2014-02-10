#include "timer.h"
#include <limits.h>

Timer::Timer() : accumulated_nsec(0)
{
}


void Timer::getTime(timespec &tp)
{
    clock_gettime(CLOCK_MONOTONIC, &tp);
}


void Timer::add(const timespec startTp)
{
    timespec currentTp;
    clock_gettime(CLOCK_MONOTONIC, &currentTp);

    ulong startNanoSec = startTp.tv_sec*1000000000 + startTp.tv_nsec;
    ulong currentNanoSec = currentTp.tv_sec*1000000000 + currentTp.tv_nsec;

    __sync_add_and_fetch(&accumulated_nsec, currentNanoSec - startNanoSec);
}


ulong Timer::getAccumulatedMsec()
{
    return accumulated_nsec/1000000;
}
