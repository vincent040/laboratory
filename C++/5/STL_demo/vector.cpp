#include "wrap.h"

void dec2oct()
{
    vector<int> v;

    cout << "请输入一个要转化的十进制数：";
    int n, tmp;
    cin >> n;
    tmp = n;

    while(tmp > 0)
    {
        v.push_back(tmp%8);
        tmp /= 8;
    }

    cout << n << "所对应的八进制数是：0";
    while(v.size() > 0)
    {
        cout << v.back();
        v.pop_back();
    }
    cout << endl << endl;
}
