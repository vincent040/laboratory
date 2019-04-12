#include <iostream>

using namespace std;

int main(void)
{
    char step = 'a' - 'A';

#if 0
    cout << "请输入任意一个字母:" << endl;
    char ch;

    while(1)
    {
        cin >> ch;

        if(isupper(ch))
            cout << ch << "-->" << char(ch + step) << endl;

        else if(islower(ch))
            cout << ch << "-->" << char(ch - ('a'-'A')) << endl;

        else
            cout << "invalid inputs!" << endl;
    }
#endif

#if 1
    cout << "请输入一串字符:" << endl;
    string s;

    while(1)
    {
        cin >> s;

        cout << s << "-->";
        for(unsigned int i=0; i<s.length(); ++i)
        {
            if(isupper(s[i]))
                cout << char(s[i] + step);

            else if(islower(s[i]))
                cout << char(s[i] - step);

	    else
		cout << s[i];
        }
        cout << endl;
    }
#endif

    return 0;
}

