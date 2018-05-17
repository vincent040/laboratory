#ifndef __MYHEAD_H__
#define __MYHEAD_H__

//添加别的头文件
#include <stdio.h>

//普通函数声明
int int_sum(int, int);
float float_sum(float, float);

//结构体、联合体、枚举的定义
struct node
{
	int data;
};

union fruit
{
	int apple;
};

enum color{red, blue, yellow};

//内联函数的定义
inline int max(int a, int b)
{
	return a>b?a:b;
}

//宏定义
#define PI 3.14
#define MAX(a, b) \
	({ \
		typeof(a) _a = a; \
		typeof(b) _b = b; \
		_a > _b ? _a : _b; \
	})

//全局变量
int error;

#endif
