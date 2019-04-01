#include <iostream>

using namespace std;

int main()
{
    string s1, s2;

    cout << "请输入第一个字符串:";
    cin >> s1;

    cout << "请输入第二个字符串:";
    cin >> s2;

    string s = s1 + s2;

    cout << "s:" << s << endl;

    return 0;
}

