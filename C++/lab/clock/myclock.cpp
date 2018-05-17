#include <iostream>
#include "myclock.h"

using namespace std;

myclock::myclock(void)
{
    hour   = 0;
    minute = 0;
    second = 0;
}

myclock::myclock(int hr, int min, int sec)
{
    hour   = hr;
    minute = min;
    second = sec;
}

void myclock::setTime(int hr, int min, int sec)
{
    hour   = hr;
    minute = min;
    second = sec;
}

void myclock::showTime()
{
    cout << hour << ":" << minute << ":" << second << endl;
}
