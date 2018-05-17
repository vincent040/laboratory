#include "wrap.h"

// 学生类
class student
{
public:
    student(){}
    student(string name, string gender, float score=0);
    void display() const;
    float score()const{return _score;}
    string name()const{return _name;}

private:
    string _name;
    string gender;
    float _score;
};

student::student(string n, string g, float s)
    :_name(n), _score(s), gender(g)
{}

void student::display() const
{
    cout << "姓名：" << this->name() << "\t";
    cout << "性别：" << gender<< "\t";
    cout << "分数：" << this->score() << endl;
}

class comp
{
public:
    bool operator()(const student &lh, const student &rh) const
    {
        return lh.score() < rh.score();
    }
};

using std::set;

void rankingScore()
{
    student Jack("Jack", "男", 88.5);
    student Rose("Rose", "女", 75.5);
    student Bill("Bill", "男");

    set<student, comp> class01;

    class01.insert(Jack);
    class01.insert(Rose);
    class01.insert(Bill);

    cout << "所有学生分数排名：" << endl;
    for(set<student, comp>::iterator p = class01.begin();
        p != class01.end(); p++)
    {
        (*p).display();
    }
    cout << endl;
}
