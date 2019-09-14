////////////////////////////////////////////////
//
// Copyright(C), 广州粤嵌通信科技股份有限公司
//
// 作者: Vincent Lin (林世霖)
//
// 微信公众号: 秘籍酷
// 技术交流群: 260492823（QQ群）
// GitHub链接: https://github.com/vincent040
//
// 描述: 类模板
//
////////////////////////////////////////////////

#include <iostream>

using namespace std;

template <typename T1, typename T2>
class node
{
public:
    node(){cout << "无特化" << endl;}
private:
    T1 a;
    T2 b;
};

template <typename T1>
class node<T1, string>
{
public:
    node(){cout << "偏特化1" << endl;}
private:
    T1 a;
    string b;
};

template <typename T2>
class node<string, T2>
{
public:
    node(){cout << "偏特化2" << endl;}
private:
    string a;
    T2 b;
};


template <>
class node<double, string>
{
public:
    node(){cout << "全特化" << endl;}
private:
    double a;
    string b;
};

// 无特化：
// node<..., ...>

// 偏特化1：
// node<..., string>

// 偏特化2：
// node<string, ...>

// 假如调用 node<string, string> 将引起二义性

// 全特化：
// node<double, string>

int main()
{
    node<double, string> a;
    node<int, string>    b;
    node<string, short> c;
    node<short, double> d;
}
