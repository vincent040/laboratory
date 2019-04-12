///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/5_polymorphism/myClock/myClock.h
// 日期：2017-10
// 描述：计时器myClock类的设计
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef MYCLOCK_H
#define MYCLOCK_H

#include <iostream>
#include <iomanip>

using namespace std;

class myClock
{
private:
    int second;
    int minute;

public:
    myClock(int m=0, int s=0);

    myClock &operator++(); 	 // 前缀：++clock
    myClock  operator++(int); // 后缀：clock++

    friend ostream &operator<<(ostream &out, myClock &c);
};

#endif // MYCLOCK_H
