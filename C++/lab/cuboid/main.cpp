#include "cuboid.h"

using namespace std;

int main()
{
    cuboid c1(2,3,4);
    cout << "c1的体积是：" << c1.volume() << endl;

    // const对象只能调用const类方法
    cuboid const c2(1,2,3);
    cout << "c2的体积是：" << c2.volume() << endl;

    cout << "c1的颜色是：" << c1.color() << endl; // 调用rectangle::color();
    cout << "c2的颜色是：" << c2.color() << endl; // 调用rectangle::color()const;

    return 0;
}
