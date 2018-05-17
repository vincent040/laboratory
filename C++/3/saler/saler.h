///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/3_class/saler.h
// 日期：2017-10
// 描述：saler类的设计
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef SALER_H
#define SALER_H

#include "product.h"

class saler
{
private:
    double totalCost;   // 总成本
    double totalAmount; // 总销售额
    double _profitRate; // 利润率＝（总销售额➖总成本）➗总成本

    // 每次发生销售行为之后，调用该私有成员方法更新销售员利润率
    void updateProfitRate();

public:
    saler(double c=0.0, double a=0.0, double p=0.0);

    void soldGoods(product &rhs, int quantity, double extraDiscount);

    double profitRate();
};

#endif // SALER_H
