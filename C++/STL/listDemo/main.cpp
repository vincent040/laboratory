#include <list> // 双向链表
#include "student.h"
#include "cmp.h"

using namespace std;

int main()
{
    // list的特点:
    // 1，双向循环链表，提供时间复杂度为O(1)插入和删除效率
    // 2，不支持随机访问
    // 3，空间效率比 forward_list 稍低
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

    // 提供一种针对特定数据的比较器对象
    cout << "学生信息（默认升序）:" << endl;
    a.sort( cmp<student<string, int> >());
    for(list< student<string, int> >::const_iterator it = a.begin();
        it != a.end(); it++)
    {
        (*it).info();
    }

    cout << "学生信息（降序）:" << endl;
    a.sort( (cmp<student<string, int> >)(cmp<student<string, int> >::DES));
    for(list< student<string, int> >::const_iterator it = a.begin();
        it != a.end(); it++)
    {
        (*it).info();
    }

    return 0;
}
