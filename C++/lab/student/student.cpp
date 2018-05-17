#include "student.h"

unsigned int Student::quantity = 0;
double Student::totalScore = 0.0;
double Student::_averageScore = 0.0;

Student::Student(string name, double score)
{
    ++quantity;
    totalScore += score;

    this->num = quantity;
    this->name = name;
    this->score = score;

    // 更新平均分
    updateAverageScore();
}

void Student::setName(string name)
{
    this->name = name;
}

void Student::setScore(double newScore)
{
    totalScore += (newScore - this->score);
    this->score = newScore;

    // 更新平均分
    updateAverageScore();
}

void Student::updateAverageScore()
{
    _averageScore = totalScore / quantity;
}

void Student::show()
{
    cout << "学号：" << num  << endl;
    cout << "姓名：" << name << endl;
    cout << "分数：" << score<< endl;
    cout << "-*-*-*-*-*-*-*-*-" << endl;
}
