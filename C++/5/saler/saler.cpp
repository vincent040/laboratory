#include "saler.h"
#include "product.h"
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

saler::saler()
{

}

void saler::soldGoods(product &p, int quantity, float discount)
{
    if(p.price()*discount <= p.cost())
        throw badDiscount(this->name, "折扣太低");

    if(quantity >= 1000)
        throw runtime_error("恶作剧");

    // 出售某一种具体的商品
    p.sold(quantity, discount);

    _totalCost += p.cost()*quantity;

    updateTotalProfit(p, quantity, discount);
    updateProfitRate();
}

void saler::showInfo() const
{
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(2);

    cout << this->name << "的业绩：" << endl;
    cout << "总利润：" << this->_totalProfit << endl;
    cout << "利润率：" << this->_profitRate  << endl << endl;
}

// 更新总利润
void saler::updateTotalProfit(product &p,
                      int quantity, float discount)
{
    // 总售价　－　总成本
    _totalProfit += (p.price()*discount - p.cost())*quantity;
}

// 更新利润率
void saler::updateProfitRate()
{
    _profitRate = _totalProfit/_totalCost;
}
