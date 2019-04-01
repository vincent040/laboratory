#include <iostream>
#include <string>

using namespace std;

void swap(string &s)
{
    for(int i=0; i<s.length(); i++)
    {
        s[i] = islower(s[i]) ? toupper(s[i]) : tolower(s[i]);
    }
}

int main()
{
    string s = "ABcdE";
    swap(s);

    cout << s << endl;

    return 0;
}

