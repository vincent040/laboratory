////////////////////////////////////////////////////
//
//  Copyright(C), 广州粤嵌通信科技股份有限公司
//
//  作者: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
//  文件: lab/C++/4_derive_inherit/card/card.h
//  描述:card类的设计
//
////////////////////////////////////////////////////

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

/* ===== 基类 ===== */
class card
{
protected:
    string bank;  // 发卡行
    string owner; // 户名

    unsigned number; // 卡号

public:
    // 发卡行名称和卡片所有者是必须的，其他信息可选
    card(string bank, string owner);
    card(string bank, string owner, unsigned number);

    // 以下是三个必须被继承并实现的纯虚函数
    virtual void enquiry(void) = 0;  // 查询卡片信息
    virtual void deposit(float  amount) = 0; // 存款
    virtual bool withdraw(float amount) = 0; // 取款
};


/* ===== 派生类: 储蓄卡 ===== */
class cashCard : public card
{
protected:
    float balance;

public:
    // 发卡行名称和卡片所有者是必须的，其他信息可选
    cashCard(string bank, string owner, float balance=0.0);
    cashCard(string bank, string owner, unsigned number,
                                        float balance=0.0);

    // 基类的纯虚函数
    void enquiry();

    // 新增的方法
    void deposit(float  amount);
    bool withdraw(float amount);
};


/* ===== 派生类: 信用卡 ===== */
class creditCard : public cashCard
{
private:
    const float limit = 3000.00;
    const float interestRate = 0.035;

    float debt;

public:
    // 发卡行名称和卡片所有者是必须的，其他信息可选
    creditCard(string bank, string owner,
                        float balance=0.0, float debt=0.0);
    creditCard(string bank, string owner, unsigned number,
                        float balance=0.0, float debt=0.0);

    void enquiry();
    bool withdraw(float amount);

    // 新增的方法
    void refund(float amount);
};

#endif // CARD_H
