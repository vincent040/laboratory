#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using std::string;
using std::cout;
using std::endl;

template <typename T1, typename T2>
class student
{
    T1 _name;
    T2 _age;

public:
    student(T1 n, T2 a);

    const T1 &name()const{return _name;}
    const T2 &age()const {return _age;}

    void info()const;
};

template <typename T1, typename T2>
student<T1, T2>::student(T1 n, T2 a)
    :_name(n), _age(a)
{
}

template <typename T1, typename T2>
void student<T1, T2>::info()const
{
    cout << "姓名:" << this->name() << ", ";
    cout << "年龄:" << this->age()  << endl;
}

#endif // STUDENT_H
