///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/3_class/date_time/__time.h
// 日期：2017-10
// 描述：时间类（__Time）设计
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef __TIME_H
#define __TIME_H

// 包含头文件，获取类的定义，才可以使用类作用域符::来取类成员
#include "__date.h"

class __Time
{
private:
    int _hour;
    int _minute;
    int _second;

    // 设置时、分、秒
    void setH(int h){_hour  = h;}
    void setM(int m){_minute= m;}
    void setS(int s){_second= s;}

    // 获取时、分、秒
    int hour()  {return _hour;  }
    int minute(){return _minute;}
    int second(){return _second;}

public:
    __Time();
    __Time(int h, int m, int s);

    void display();

    friend void display_date_time(__Date &d, __Time &t);

    // friend class Date_;
    friend void __Date::display_time(__Time &t);
};

#endif // __TIME_H
