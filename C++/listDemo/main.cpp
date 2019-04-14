#include <list> // 双向链表
#include "student.h"
#include "cmp.h"

using namespace std;

int main()
{
    list< student<string, int> > a;

    student<string, int> Jack("Jack", 21);
    student<string, int> Rose("Rose", 24);
    student<string, int> Bill("Bill", 18);

    a.push_back(Jack);
    a.push_back(Rose);
    a.push_back(Bill);

    cout << "学生信息:" << endl;
    for(list< student<string, int> >::const_iterator it = a.begin();
        it != a.end(); it++)
    {
        (*it).info();
    }

    cout << "学生信息:" << endl;
    a.sort( cmp<student<string, int> >());
    for(list< student<string, int> >::const_iterator it = a.begin();
        it != a.end(); it++)
    {
        (*it).info();
    }

    return 0;
}
