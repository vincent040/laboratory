#ifndef SHOE_H
#define SHOE_H

#include <iostream>
#include <string>

using std::string;

// sheo是鞋子类，一个对象就是某品牌的一款鞋子
class shoe
{
public:
    shoe();
    ~shoe();
    shoe(float cost, float price);

    void setPrice(float newPrice);
    void sale(int number, float discount);

    static void showProfit();	  // 总利润
    static void showProfitRate(); // 总利润率

private:
    float price;	// 售价
    float discount; // 折扣
    float cost;		// 单品成本

    static float	totalCost;		 // 总成本
    static float	totalSaleVolume; // 总销售额

};

#endif // SHOE_H
