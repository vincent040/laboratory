///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/2_class/student.h
// 日期：2017-10
// 描述：一个简单的包含学号、姓名和分数的student类
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class student
{
public:
    student();
    student(unsigned int number, string name, float score=0.0);

    void info();

private:
    unsigned int number;
    string name;
    float score;
};

#endif // STUDENT_H
