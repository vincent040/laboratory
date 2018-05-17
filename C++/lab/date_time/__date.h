///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/3_class/date_time/__date.h
// 日期：2017-10
// 描述：日期类（__Date）设计
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef __DATE_H
#define __DATE_H

// 前向声明，用来定义该来的引用或者指针
class __Time;

class __Date
{

    int _year;
    int _month;
    int _day;

    // 设置年、月、日
    void setY(int y){_year = y;}
    void setM(int m){_month= m;}
    void setD(int d){_day  = d;}

    // 获取年、月、日
    int year() {return _year; }
    int month(){return _month;}
    int day()  {return _day;  }

public:
    __Date();
    __Date(int y, int m, int d);

    // 公有成员函数：一般只有他才能访问对象的私有成员
    void display();

    // 友元函数：可以跟成员函数一样访问类和对象的
    // friend关键字的作用：
    // 1，虽然以下函数在类中声明，但他不是成员函数，不能使用.或者->来调用
    // 2，虽然以下函数不是成员函数，但他与成员函数的访问权限相同
    friend void display_date_time(__Date &d, __Time &t);

    void display_time(__Time &t);
};

#endif // __DATE_H
