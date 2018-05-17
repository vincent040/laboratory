#include <iostream>
#include "myclock.h"

using namespace std;

int main(void)
{
    myclock *c = new myclock;

    // 显示默认的时间（00:00:00）
    c->showTime();

    // 设置自定义时间（15:59:57），并显示当前时间
    c->setTime(15, 59, 57);
    c->showTime();

    return 0;
}

