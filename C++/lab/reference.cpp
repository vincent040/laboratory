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
// 描述: 左值引用、右值引用以及它们的const类型
//
////////////////////////////////////////////////

#include <iostream>
#include <string>

using namespace std;

// 左值引用
// 1、可影响实参
// 2、可修改
// 3、不可接受右值表达式
int f1(int &a)
{
	a = 200;
	string s;
	s.append(__FUNCTION__).append(":").append(to_string(a));
	cout << s << endl;
}

// 右值引用
// 1、不影响实参
// 2、可修改
// 3、可接受右值表达式
int f2(int &&a)
{
	a = 300;
	string s;
	s.append(__FUNCTION__).append(":").append(to_string(a));
	cout << s << endl;
}

// const左值引用
// 1、不影响实参
// 2、不可修改
// 3、可接受右值表达式
int f3(const int &a)
{
	//a = 300;
	string s;
	s.append(__FUNCTION__).append(":").append(to_string(a));
	cout << s << endl;
}

// const右值引用
// 1、不影响实参
// 2、不可修改
// 3、可接受右值表达式
int f4(const int &&a)
{
	//a = 300;
	string s;
	s.append(__FUNCTION__).append(":").append(to_string(a));
	cout << s << endl;
}


int main(int argc, char **argv)
{
	int a = 100;
	string s;

	f1(a);
	s.append(__FUNCTION__).append(":").append(to_string(a));
	cout << s << endl;

	f2(a+1);
	s.clear();
	s.append(__FUNCTION__).append(":").append(to_string(a));
	cout << s << endl;

	f3(a+2);
	s.clear();
	s.append(__FUNCTION__).append(":").append(to_string(a));
	cout << s << endl;

	f4(a+3);
	s.clear();
	s.append(__FUNCTION__).append(":").append(to_string(a));
	cout << s << endl;

	return 0;
}

