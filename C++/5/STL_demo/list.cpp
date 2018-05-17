#include "wrap.h"

void rearrange()
{
    list<int> mylist;

    cout << "你想要多少个自然数？";
    int n;
    cin >> n;

    // 放入自然数
    for(int i=1; i<=n; i++)
    {
        mylist.push_back(i);
    }

    cout << "自然数原始序列：" << endl;
    show< list<int> >(mylist);

    // 从后往前，遍历链表
    for(list<int>::reverse_iterator p = mylist.rbegin();
        p != mylist.rend(); p++)
    {
        // 如果是偶数，则移动到链表的末尾
        if(*p % 2 == 0)
        {
            int tmp = *p;

            mylist.remove(tmp);
            mylist.push_back(tmp);
        }
    }

    cout << "奇偶数重新排列之后的序列：" << endl;
    show< list<int> >(mylist);
    cout << endl;
}
