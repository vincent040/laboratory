#include <iostream>
#include "point.h"

using namespace std;

int main()
{
    point p1;
    cout << "p1:[" << p1.getX() << "," << p1.getY() << "]" << endl;

    p1.setX(100);
    p1.setY(200);

    cout << "p1:[" << p1.getX() << "," << p1.getY() << "]" << endl;

    point p2(3.14159, 2.71818);

    cout << "p2:[" << p2.getX() << "," << p2.getY() << "]" << endl;

    return 0;
}

