///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/4_derive_inherit/card/card.cpp
// 日期：2017-10
// 描述：card类的成员函数实现
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include <cmath>
#include "card.h"

/*********************** 基类：card ************************/
card::card(string bank, string owner)
{
    this->bank  = bank;
    this->owner = owner;

    srand(time(NULL));
    number = rand();
}

card::card(string bank, string owner, unsigned number)
{
    this->bank  = bank;
    this->owner = owner;
    this->number= number;
}

/********************** 派生类：储蓄卡 ***********************/

cashCard::cashCard(string bank, string owner, float b)
:card(bank, owner)
{
    balance = b;
}

cashCard::cashCard(string bank, string owner, unsigned number,
                                                float b)
:card(bank, owner, number)
{
    balance = b;
}

void cashCard::enquiry()
{
    cout << "户名：" << owner << endl;
    cout << "卡号：" << number << endl;
    cout << "余额：" << balance << endl;
}

void cashCard::deposit(float amount)
{
    if(amount <= 0)
        return;

    balance += amount;

    cout << "系统检测到您的卡号为[" << number << "]的银行卡存入了￥";
    cout << amount << ", 余额为￥" << balance << "[" << bank;
    cout << "]" << endl;
}

bool cashCard::withdraw(float amount)
{
    if(amount < 0)
    {
        cerr << "对不起，取款金额不能为负数！" << endl;
        return false;
    }

    if(balance < amount)
    {
        cerr << "对不起！余额不足！" << endl;
        return false;
    }

    balance -= amount;
    cout << "您卡片的余额：￥" << balance << endl;
    return true;
}

/********************** 派生类：信用卡 ***********************/

creditCard::creditCard(string bank, string owner,
                                float balance, float debt)
:cashCard(bank, owner)
{
    this->debt = debt;
    this->balance = balance;
}

creditCard::creditCard(string bank, string owner,
                unsigned number, float balance, float debt)
:cashCard(bank, owner, number)
{
    this->debt = debt;
    this->balance = balance;
}

void creditCard::enquiry()
{
    cout << "户名：" << owner  << endl;
    cout << "卡号：" << number << endl;
    cout << "余额：" << balance<< endl;

    cout << "额度：" << limit << endl;
    cout << "利息：" << interestRate << endl;
    cout << "负债：" << debt  << endl;
}

bool creditCard::withdraw(float amount)
{
    if(amount < 0)
    {
        cerr << "对不起！消费或取款数额必须是正数！" << endl;
        return false;
    }

    if(balance < amount) // 透支
    {
        float overdraw = abs(balance - amount);

        if(overdraw > limit-debt)
        {
            cerr << "对不起！额度不足！" << endl;
            return false;
        }

        balance = 0;
        debt += overdraw*(1+interestRate);
        cout << "消费或者取款成功！您当前欠款￥" << debt;
        cout << "（含利息）" << endl;
        return true;
    }

    balance -= amount;
    cout << "消费或者取款成功！您当前余额￥" << balance << endl;
    return true;
}

void creditCard::refund(float amount)
{
    if(amount < 0)
    {
        cerr << "对不起！还款数额必须是正数！" << endl;
    }

    debt -= amount;
    cout << "您当前欠款￥" << debt << "（含利息）" << endl;
}
