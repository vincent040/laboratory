#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

class Student
{
private:
    /**** 类静态成员 ****/
    // 1，不可以virtual
    static double _averageScore;
    static unsigned int quantity;
    static double totalScore;

    static void updateAverageScore();

    /**** 普通成员 ****/
    unsigned int num;
    string name;
    double score;



public:
    Student(string name="", double score=0.0);

    void setName(string name);
    void setScore(double score);

    void show();

    // 类静态方法
    static double averageScore(){return _averageScore;}
};

#endif // STUDENT_H
