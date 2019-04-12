///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/3_class/product.h
// 日期：2017-10
// 描述：基类（product）及其派生类的设计
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>

// 基类：产品
class product
{
protected:
    // 类静态成员
    static double _totalAmount; // 总销售额

    // 类普通成员
    double _cost;  // 单件成本（不同品牌成本不一样）
    double _price; // 售价（原价）
    double _discount; // 折扣

public:
    // 构造函数：初始化单件成本、售价、折扣
    product(double cost=0.0, double price=0.0, double discount=0.0);

    /* ============== 类静态方法 ============ */
    // 获取商品的总销售额
    static double totalAmount(){return _totalAmount;}


    /* ============== 普通类方法 ============ */
    // 获取商品的单件成本、售价、折扣
    double cost()const{return _cost;}
    double price()const{return _price;}
    double discount()const{return _discount;}

    // 设置商品的售价、折扣
    void setCost(double newCost){_cost = newCost;}
    void setPrice(double newPrice){_price = newPrice;}
    void setDiscount(double newDiscount){_discount = newDiscount;}

    // 出售行为（纯虚函数）
    virtual void sold(int quantity, double extraDiscount)=0;
};

// 派生类：洗发水
class shampoo : public product
{
private:
    static int _totalSoldCount; // 总已售数量

public:
    shampoo(double cost, double price, double discount);
    virtual void sold(int soldCount, double extraDiscount);

    static int totalSoldCount(){return _totalSoldCount;}
};

// 派生类：苹果
class apple : public product
{
private:
    static double _totalSoldWeight;

public:
    apple(double cost, double price, double discount);
    virtual void sold(int soldWeight, double extraDiscount);

    static double totalWeight(){return _totalSoldWeight;}
};

#endif // PRODUCT_H
