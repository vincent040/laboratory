////////////////////////////////////////////////
//
//  Copyright(C), 广州粤嵌通信科技股份有限公司
//
//  作者: Vincent Lin (林世霖)
//
//  微信公众号: 秘籍酷
//  技术交流群: 260492823（QQ群）
//  GitHub链接: https://github.com/vincent040
//
//  描述: 函数模板及其特化
//
////////////////////////////////////////////////

#include <iostream>

using namespace std;

template <typename T1, typename T2>
void f(T1 a, T2 b)
{
	cout << "通用版本" << endl;
}


template <typename T>
void f(T a, string s)
{
	cout << "重载版本1" << endl;
}

template <typename T>
void f(T a, const char *s)
{
	cout << "重载版本2" << endl;
}

template <typename T>
void f(int *p, T b)
{
	cout << "重载版本3" << endl;
}

template<>
void f(int a, int b)
{
	cout << "重载版本4" << endl;
}

template<>
void f<int, int *>(int a, int *b)
{
	cout << "全特化版本" << endl;
}

void f(int a, int b)
{
	cout << "普通函数" << endl;
}

int main(int argc, char **argv)
{
	f(1, 2);     // 普通函数
	f<>(1, 2);   // 全特化版本
	f(1.1, 1.2); // 通用版本

	// 偏特化版本1
	string s="ab";
	f(1, s);

	// 偏特化版本2
	f(100, "xy");
	f(1.1, "xy");
	f("a", "xy");

	// 偏特化版本3
	int a = 100;
	f(&a, 1.1);
	f(&a, 100);
	//f(&a, "a");
	//f(&a,  s );

	//f<int, int>(1, 2);
	f(1, &a);

	return 0;
}
