////////////////////////////////////////////////////
//
//  Copyright(C), 广州粤嵌通信科技股份有限公司
//
//  作者: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
//  文件: lab/C++/4_derive_inherit/complexNumber/complexNumber.h
//  描述: 复数类complexNumber的设计。
//
////////////////////////////////////////////////////

#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <iostream>

using namespace std;

class complexNumber
{
private:
    float realNumber;
    float imaginaryUnit;

public:
    complexNumber(float r=0, float i=0);

    void setValue(float r, float i);

    complexNumber operator+(const complexNumber &c);
    complexNumber operator-(const complexNumber &c);
    complexNumber operator*(const complexNumber &c);
    complexNumber operator/(const complexNumber &c);
    complexNumber &operator=(const complexNumber &c);

    // 为了符合标准输出的习惯，将operator<<声明为友元函数
//    friend ostream &operator<<(ostream &o, const complexNumber &c);

    void show()const;
};

#endif // COMPLEXNUMBER_H
