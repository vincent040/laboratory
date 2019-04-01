///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/3_class/date_time/__time.cpp
// 日期：2017-10
// 描述：时间类（__Time）成员函数的实现
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include "__time.h"

using namespace std;

__Time::__Time()
{
    _hour = 0;
    _minute = 0;
    _second = 0;
}

__Time::__Time(int h, int m, int s)
{
    _hour = h;
    _minute = m;
    _second = s;
}

void __Time::display()
{
    cout << setfill('0') << setw(2);

    cout << hour()   << ":";
    cout << minute() << ":";
    cout << second() << endl;
}
