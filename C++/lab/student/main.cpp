#include <iostream>
#include "student.h"

using namespace std;

int main()
{
    cout << endl << "总体平均分：" << Student::averageScore() << endl;
    Student Jack, Rose("Rose"), Bill("Bill", 89.5);

    Jack.setName("Jack");

    Jack.setScore(60.5);
    Rose.setScore(99.5);


    Jack.show();
    Rose.show();
    Bill.show();

    cout << endl << "总体平均分：" << Student::averageScore() << endl;

    return 0;
}
