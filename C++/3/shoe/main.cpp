#include <iostream>
#include "shoe.h"

using namespace std;

int main()
{
    // 耐克某款女鞋
    shoe Nike(  580 /*成本*/,  999 /*零售价*/);
    // 销售情况
    Nike.sale(1, 90 /* 9折 */);
    Nike.sale(2, 85 /* 85折*/);
    Nike.sale(5, 70 /* 7折 */);

    shoe::showProfit();
    shoe::showProfitRate();

    /////////////////////////////////////////////

    // 阿迪某款男鞋
    shoe Adidas(680 /*成本*/, 1399 /*零售价*/);
    // 销售情况
    Adidas.sale(5, 50 /* 半价促销 */);

    shoe::showProfit();
    shoe::showProfitRate();


    return 0;
}

