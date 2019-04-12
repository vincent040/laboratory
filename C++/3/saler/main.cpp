///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/3_class/main.cpp
// 日期：2017-10
// 描述：使用saler类和product及其派生类实现销售利润率管理
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include <iostream>

#include "product.h"
#include "saler.h"

using namespace std;

int main()
{
    saler *Jack = new saler;
    saler *Rose = new saler;
    saler *Bill = new saler;

    shampoo Rejoice(15, 30, 0.1);

    Jack->soldGoods(Rejoice, 5, 0.0);
    Rose->soldGoods(Rejoice, 12, 0.03);
    Bill->soldGoods(Rejoice, 100, 0.1);

    shampoo HeadAndShoulders(35, 60, 0.0);
    Jack->soldGoods(HeadAndShoulders, 20, 0.0);


    cout << "洗发水总销售额：" << Rejoice.totalAmount() << endl;

    cout << "Jack的利润率：" << Jack->profitRate() << endl;
    cout << "Rose的利润率：" << Rose->profitRate() << endl;
    cout << "Bill的利润率：" << Bill->profitRate() << endl;


    apple Fuji(2.8, 5, 0);

    Jack->soldGoods(Fuji, 10, 0.1);

    return 0;
}
