///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/3_class/date_time/__date.cpp
// 日期：2017-10
// 描述：日期类（__Date）成员函数的实现
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>

#include "__date.h"
#include "__time.h"

using namespace std;

__Date::__Date()
{
    _year = 1900;
    _month = 1;
    _day = 1;
}

__Date::__Date(int y, int m, int d)
{
    _year = y;
    _month = m;
    _day = d;
}

void __Date::display()
{
    cout << setfill('0') << setw(2);

    cout << year()  << "/";
    cout << month() << "/";
    cout << day()   << endl;
}

void __Date::display_time(__Time &t)
{
    cout << "{";
    cout << setfill('0') << setw(2);

    cout << t.hour()  << ":";
    cout << t.minute()<< ":";
    cout << t.second()<< "}" << endl;
}
