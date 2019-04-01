#include "shoe.h"

using std::cout;
using std::endl;

float shoe::totalCost   = 0.0;
float shoe::totalSaleVolume = 0.0;

shoe::shoe()
{

}

shoe::shoe(float cost, float price)
{
    this->cost = cost;
    this->price= price;
}

shoe::~shoe()
{

}


void shoe::setPrice(float newPrice)
{
    this->price = newPrice;
}

void shoe::sale(int number, float discount)
{
    this->totalCost       += number * cost;
    this->totalSaleVolume += number * price * discount/100;
}

void shoe::showProfit()
{
    cout << "总利润：￥" << totalSaleVolume - totalCost << endl;
}

void shoe::showProfitRate()
{
    float profit = totalSaleVolume - totalCost;
    cout << "利润率：" << 100 * (profit/totalCost)  << "%";
    cout << endl << endl;
}
