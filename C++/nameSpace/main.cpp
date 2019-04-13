#include <iostream>
#include "names.h"

using namespace std;

namespace myspace {

int x=100;
int y=200;

}

int x = 400;

namespace myspace {

int z=300;

    namespace myspace2 {

    int x=1;

    }

    class abc
    {
    public:
        int x;
    };

}

int main()
{
    using namespace myspace;
//    using myspace::x;
//    using myspace::y;

    cout << a << endl;
    cout << ::x << endl;
    cout << myspace::x << endl;
    cout << y << endl;
    cout << z << endl;
    cout << myspace2::x << endl;

    return 0;
}
