///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/2_class/student.cpp
// 日期：2017-10
// 描述：student类的成员函数实现
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include "student.h"
#include <iostream>

student::student()
{}

student::student(unsigned int number, string name, float score)
{
    this->number = number;
    this->name   = name;
    this->score  = score;
}

void student::info()
{
    cout << "number: " << number << endl;
    cout << "name:   " << name   << endl;
    cout << "score:  " << score  << endl;
}


