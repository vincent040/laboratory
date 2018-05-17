#include <iostream>
#include "product.h"
#include "saler.h"

using namespace std;

int main()
{
    apple   fushi        (2 /*成本*/, 5 /*售价*/);
    shampoo head_shoulder(20/*成本*/, 50/*售价*/);

    saler Jack("Jack");
    try{
        Jack.soldGoods(fushi, 1, 1);
        Jack.soldGoods(head_shoulder, 1, 1);

        Jack.showInfo();
    }
    catch(badDiscount &e)
    {
        cout << e.what() << endl;
        cout << e.name() << "，你还想不想干了？" << endl;
    }


    saler Rose("Rose");
    try{
        Rose.soldGoods(fushi, 200, 0.5);
        Rose.soldGoods(head_shoulder, 900, 0.5);

        Rose.showInfo();
    }
    catch(badDiscount &e)
    {
        cout << e.what() << endl;
        cout << e.name() << "，你还想不想干了？" << endl;
    }
    catch(...)
    {
        cerr << "糟糕！发生了不可预知的错误！但生活还得继续。。。" << endl;
    }


    cout.unsetf(ios_base::floatfield);
    cout << endl;
    cout << "苹果卖了："  << apple::totalWeight()<< "斤" << endl;
    cout << "洗发水卖了：" << shampoo::totalCount() << "瓶" << endl;
    cout << "店铺总销售额："   << product::totalAmount() << endl;

    return 0;
}

