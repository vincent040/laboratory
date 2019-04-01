#include <iostream>
#include "swimmingpool.h"

using namespace std;

int main()
{
    swimmingPool *sp2 = new swimmingPool;

    cout << "请输入泳池的半径：";
    float r;
    cin >> r;

    if(!sp2->setRadius(r))
    {
        cout << "对不起！输入错误，泳池最小半径是5米." << endl;
    }

    cout << "半径为[" << sp2->getRadius() << "米]的泳池的总造价：";
    cout << sp2->totalCost() << endl;

    return 0;
}
