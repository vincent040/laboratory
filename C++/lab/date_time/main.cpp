///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/3_class/date_time/main.cpp
// 日期：2017-10
// 描述：使用精心定义的__Date和__Time来理解友元的使用细节
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

void display_date_time(__Date &d, __Time &t)
{
    cout << "[";
    cout << setfill('0') << setw(2);

    cout << d.year()  << "年";
    cout << d.month() << "月";
    cout << d.day()   << "日" << ", ";

    cout << t.hour()   << "时";
    cout << t.minute() << "分";
    cout << t.second() << "秒]" << endl;
}

int main()
{
    __Date d(2016, 9, 18);
    __Time t(15, 30, 45);

    d.display();
    t.display();

    /* ========= 友元的使用 ==========*/

    // 1，友元函数
    display_date_time(d, t);

    // 2，友元类
    d.display_time(t);

    // 3，友元成员函数
    d.display_time(t);

    return 0;
}
