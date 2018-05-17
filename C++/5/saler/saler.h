#ifndef SALER_H
#define SALER_H

#include <string>
#include <exception>
#include <stdexcept>
#include "product.h"

using namespace std;

class saler
{
public:
    saler();
    saler(string name, float totalProfit=0,
                       float profitRate=0,
                       float totalCost=0)
        :name(name), _totalProfit(totalProfit),
         _profitRate(profitRate),_totalCost(totalCost){}

    void soldGoods(product &p, int quantity, float discount);

    float totalProfit()const{return _totalProfit;}
    float profitRage() const{return _profitRate;}
    float totalCost() const{return _totalCost;}

    void showInfo()const;

private:
    // 计算总利润
    void updateTotalProfit(product &p, int quantity, float discount);
    // 计算利润率
    void updateProfitRate();

    string name;

    float _totalProfit; // 总利润
    float _profitRate ; // 利润率
    float _totalCost;   // 总成本
};

// 继承自系统标准异常类logic_error，用以表达错误的折扣
class badDiscount : public logic_error
{
public:
    badDiscount(string name, string bad)
        :logic_error(bad), _name(name){}
    string &name(){return _name;}

private:
    string _name;
};

#endif // SALER_H
