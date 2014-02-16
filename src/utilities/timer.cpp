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

	__sync_add_and_fetch(&accumulated_nsec, getDifferenceInNsec(startTp, currentTp));
}


ulong Timer::getAccumulatedMsec()
{
	return accumulated_nsec/1000000;
}

float Timer::getElapsedMsec(const timespec &tp)
{
	timespec currentTp;
	clock_gettime(CLOCK_MONOTONIC, &currentTp);

	return getDifferenceInNsec(tp, currentTp)/1000000.0;
}


ulong Timer::getDifferenceInNsec(const timespec &startTp, const timespec &endTp)
{
	ulong startNanoSec = startTp.tv_sec*1000000000 + startTp.tv_nsec;
	ulong endNanoSec = endTp.tv_sec*1000000000 + endTp.tv_nsec;

	return endNanoSec - startNanoSec;
}
