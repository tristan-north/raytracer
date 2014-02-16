#ifndef TIMER_H
#define TIMER_H

#include <QtGlobal>
#include <time.h>

class Timer
{
public:
    Timer();
    static void getTime(timespec &tp);
    void add(const timespec startTp);
    ulong getAccumulatedMsec();
	static float getElapsedMsec(const timespec &tp);

private:
	static ulong getDifferenceInNsec(const timespec &startTp, const timespec &endTp);

    ulong accumulated_nsec;
};

#endif // TIMER_H
