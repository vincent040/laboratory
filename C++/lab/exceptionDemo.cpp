#include <iostream>
#include <string>

using namespace std;

class err
{
public:
    err(string const &s){_msg = s;}
    string &msg(){return _msg;}

private:
    string _msg;
};

void f1(int a)
{
    if(a == 1)
        throw string("abcd");

    if(a == 2)
        throw float(3.14);

    if(a == 3)
    {
        throw (err("f1失败了！"));
    }

    return;
}

int main()
{
    try
    {
        f1(3);
    }
    catch(const string s)
    {
        cerr << s << endl;
    }
    catch(float f)
    {
        cerr << f << endl;
    }
    catch(err &e)
    {
        cerr << e.msg() << endl;
    }
    catch(...)
    {
        cerr << "其他情况" << endl;
    }

    return 0;
}

