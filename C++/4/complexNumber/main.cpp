///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/5_polymorphism/complexNumber/main.cpp
// 日期：2017-10
// 描述：使用C++多态性，实现复数的四则运算
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include <iostream>
#include "complexnumber.h"

using namespace std;

int main()
{
    complexNumber a(1, 2); // a = 1+2i
    complexNumber b;
    b.setValue(5, -3); // set b = 5-3i

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    complexNumber c;
    c = a+b;
    cout << "a+b: " << c << endl;

    c = a-b;
    cout << "a-b: " << c << endl;

    c = a*b;
    cout << "a*b: " << c << endl;

    b.setValue(0, 0);
    c = a/b;
    cout << "a/b: " << c << endl;

    return 0;
}

