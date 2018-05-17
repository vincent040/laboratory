///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/5_polymorphism/complexNumber/complexNumber.cpp
// 日期：2017-10
// 描述：复数类complexNumber成员函数的实现
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include "complexnumber.h"

// 构造函数可以使用参数列表
complexNumber::complexNumber(float r, float i):realNumber(r),imaginaryUnit(i)
{
}

void complexNumber::setValue(float r, float i)
{
    realNumber = r;
    imaginaryUnit = i;
}

complexNumber complexNumber::operator+(const complexNumber &c)
{
    // 不能返回引用，因为加减乘除的耳目运算只应该产生一个结果
    // 而不应该对操作数产生任何影响，这个结果放在tmp中
    complexNumber tmp;
    tmp.setValue(this->realNumber + c.realNumber,
                 this->imaginaryUnit + c.imaginaryUnit);

    return tmp;
}

complexNumber complexNumber::operator-(const complexNumber &c)
{
    complexNumber tmp;
    tmp.setValue(this->realNumber - c.realNumber,
                 this->imaginaryUnit - c.imaginaryUnit);

    return tmp;
}

complexNumber complexNumber::operator*(const complexNumber &c)
{
    // 公式：(a+bi) * (c+di) = (ac-bd) + (bc+ad)i
    float r = this->realNumber * c.realNumber -
              this->imaginaryUnit * c.imaginaryUnit;
    float i = this->imaginaryUnit * c.realNumber +
              this->realNumber * c.imaginaryUnit;

    complexNumber tmp;
    tmp.setValue(r, i);

    return tmp;
}

complexNumber complexNumber::operator/(const complexNumber &c)
{
    // 公式：(a+bi) / (c+di) = (ac+bd)/(c^2+d^2) + ((bc-ad)/(c^2+d^2))i

    if(c.realNumber == 0 && c.imaginaryUnit == 0)
    {
        cerr << "[除数不能为0]";
    }

    float f = c.realNumber*c.realNumber + c.imaginaryUnit*c.imaginaryUnit;

    float r = (this->realNumber * c.realNumber +
               this->imaginaryUnit * c.imaginaryUnit)/f;
    float i = (this->imaginaryUnit * c.realNumber -
               this->realNumber * c.imaginaryUnit)/f;

    complexNumber tmp;
    tmp.setValue(r, i);

    return tmp;
}

complexNumber &complexNumber::operator=(const complexNumber &c)
{
    // 应该返回引用，因为赋值运算应该要对左操作数做出影响
    this->setValue(c.realNumber, c.imaginaryUnit);

    return *this;
}

void complexNumber::show() const
{
    cout << realNumber;

    if(imaginaryUnit > 0)
        cout << "+" << imaginaryUnit << "i";

    if(imaginaryUnit < 0)
        cout << imaginaryUnit << "i";
}

ostream & operator<<(ostream &out, const complexNumber &c)
{
    c.show();
//    out << c.realNumber;

//    if(c.imaginaryUnit > 0)
//        out << "+" << c.imaginaryUnit << "i";

//    if(c.imaginaryUnit < 0)
//        out << c.imaginaryUnit << "i";

    return out;
}
