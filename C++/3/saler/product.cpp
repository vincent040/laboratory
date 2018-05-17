///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/3_class/product.cpp
// 日期：2017-10
// 描述：基类（product）及其派生类成员函数的实现
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include "product.h"

double product::_totalAmount = 0.0;

int shampoo::_totalSoldCount = 0;
double apple::_totalSoldWeight = 0.0;

product::product(double cost, double price, double discount)
{
    _cost = cost;	// 成本
    _price = price; // 售价
    _discount = discount; // 折扣
}

//void product::sold(int quantity, double extraDiscount)
//{
//    // 具体的销售行为，交由具体的商品去决定如何执行
//    // 基类只负责提供接口，此处最好将sold设计为纯虚函数
//}


shampoo::shampoo(double cost, double price, double discount)
    :product(cost, price, discount)
{
}

apple::apple(double cost, double price, double discount)
    :product(cost, price, discount)
{

}

void shampoo::sold(int soldCount, double extraDiscount)
{
    // 计算折后总价
    double oldPrice = this->price() * (1-this->discount());
    double newAmount = oldPrice * soldCount * (1-extraDiscount);

    // 更新商品总销售额（静态成员）
    _totalAmount += newAmount;
    _totalSoldCount += soldCount;
}

void apple::sold(int soldWeight, double extraDiscount)
{
    // 计算折后总价
    double oldPrice = this->price() * (1-this->discount());
    double newAmount = oldPrice * soldWeight * (1-extraDiscount);

    // 更新商品总销售额（静态成员）
    _totalAmount += newAmount;
    _totalSoldWeight += soldWeight;
}
