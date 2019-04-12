///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/3_class/saler.cpp
// 日期：2017-10
// 描述：saler类成员函数的实现
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include "product.h"
#include "saler.h"

saler::saler(double c, double a, double p)
{
    totalCost   = c;
    totalAmount = a;
    _profitRate  = p;
}

void saler::soldGoods(product &rhs, int quantity, double extraDiscount)
{
    // 总成本增加
    totalCost += (rhs.cost() * quantity);

    // 总销售额增加
    double amount = rhs.price() * (1-rhs.discount()) * quantity * (1-extraDiscount);
    totalAmount += amount;

    // 更新销售员的利润率
    updateProfitRate();

    // 更新商品的出售记录
    rhs.sold(quantity, extraDiscount);
}

void saler::updateProfitRate()
{
    _profitRate = (totalAmount-totalCost) / totalCost;
}

double saler::profitRate()
{
    return _profitRate;
}
