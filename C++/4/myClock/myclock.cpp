#include "myclock.h"

myClock::myClock(int m, int s) : second(s), minute(m)
{
}

// 前缀：++clock
myClock &myClock::operator++()
{
    this->second++;

    if(this->second >= 60)
    {
        // 每60秒进1分钟
        this->second = 0;
        this->minute++;

        // 每60分钟计时器归零
        if(this->minute >= 60)
            this->minute = 0;
    }

    return *this;
}

// 后缀：clock++
myClock myClock::operator++(int)
{
    myClock tmp = *this;

    ++(*this);

    return tmp;
}

ostream &operator<<(ostream &out, myClock &c)
{
    out << setw(2);
    out << setfill('0');
    out << c.minute << ":";

    out << setw(2);
    out << c.second;

    return out;
}
