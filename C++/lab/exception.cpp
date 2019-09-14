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
//  描述: 异常
//
////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

class err
{
public:
        err(string const &s){_msg = s;}
        string &msg(){return _msg;}

private:
        string _msg;
};

void f1(int a)
{
	// 抛出的异常，可以是普通变量，也可以是类对象
	// 抛出的异常对象与函数传参类似，被传送至catch语句
	// 但有以下两点不同:
	// ① 异常对象能持续追踪try...catch语句，直到遇到匹
	// 配的类型，或者程序退出
	// ② 异常对象在匹配的catch语句之后仍然存在不会释放
        if(a == 1)
                throw "abcd";

	else if(a == 2)
                throw 3.14;

	else if(a == 3)
        {
                throw (runtime_error("运行时错误"));
        }

	else if(a == 4)
        {
                throw (err("自定义错误"));
        }
	else
	{
		throw ('a');
	}

        return;
}

void f2(int n)
{
	try
	{
		f1(n);
	}
	catch(const char *e)
	{
		cerr << "错误:" << e << endl;
	}
	catch(double e)
	{
		cerr << "错误:" << e << endl;
	}
}

int main(void)
{
	int n;
        while(1)
	{
		cin >> n;

		try
		{
			f2(n);
		}
		catch(runtime_error &e)
		{
			string errstr;
			errstr.append(__FUNCTION__).append(":").append(e.what());
			cerr << errstr << endl;
		}
		catch(err &e)
		{
			string errstr;
			errstr.append(__FUNCTION__).append(":").append(e.msg());
			cerr << errstr << endl;
		}
		catch(...)
		{
			cerr << "其他未知情况" << endl;
		}
	}

        return 0;
}
