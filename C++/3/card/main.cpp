///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/4_derive_inherit/card/main.cpp
// 日期：2017-10
// 描述：使用储蓄卡、信用卡的案例理解基类与派生类
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include <iostream>
#include "card.h"

using namespace std;

int main()
{
    // 工商银行-储蓄卡
    cashCard card1("工商银行储蓄卡", "周星驰");
    card1.deposit(250); // 向储蓄卡存入￥250
    card1.withdraw(180);// 尝试从卡中取出￥180
    card1.withdraw(500);// 尝试再从卡中取出￥500
    card1.enquiry();	// 显示卡片的具体信息

    // 汇丰银行-信用卡
    creditCard card2("汇丰银行", "范冰冰");
    card2.withdraw(250);// 尝试从信用卡中透支￥250
    card2.enquiry();    // 显示卡片的具体信息

    card2.deposit(300); // 向信用卡存入￥300
    card2.enquiry();    // 显示卡片的具体信息，余额￥300；负债￥250+利息

    card2.refund(280);  // 还款￥280
    card2.withdraw(500);
    card2.enquiry();    // 显示卡片的具体信息，余额￥0；负债￥170+利息

    return 0;
}
