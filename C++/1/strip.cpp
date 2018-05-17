#include <iostream>
#include <cstring> // for strstr()

using namespace std;

int main()
{
#if 0
    // C语言的写法
    char s1[100], s2[100];

    bzero(s1, 100);
    printf("请输入一个字符串：\n");
    fgets(s1, 100, stdin);

    for(unsigned int i=0, j=0; i<strlen(s1); ++i)
    {
        char tmp[2] = {s1[i], '\0'};

        if(!strstr(s2, tmp))
        {
            s2[j] = s1[i];
            ++j;
        }
    }

    printf("%s", s2);

#endif


#if 1
    // C++的写法
    string s1, s2;

    cout << "请输入一个字符串：" << endl;
    cin >> s1;

    for(unsigned int i=0; i<s1.length(); ++i)
    {
        if(s2.find(s1[i], 0) == string::npos)
        {
            s2.append(1, s1[i]);
        }
    }

    cout << s2 << endl;
#endif

    return 0;
}
