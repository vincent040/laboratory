#ifndef MYCLOCK_H
#define MYCLOCK_H

class myclock
{
public:
    myclock(void);
    myclock(int hr, int min, int sec);
    ~myclock(){;}

    void setTime(int hr, int min, int sec);
    void showTime();

private:
    int hour;
    int minute;
    int second;
};

#endif // MYCLOCK_H
