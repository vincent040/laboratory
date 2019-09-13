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
//  描述:
//
////////////////////////////////////////////////

#include <iostream>
#include <cstring>

using namespace std;

template <typename T1, typename T2>
T1 maxn(T1 a[], T2 size)
{
	T1 max=a[0];
	for(int i=1; i<size; i++)
	{
		max = max>a[i] ? max : a[i];
	}
	return max;
}

template<typename T2>
const char *maxn(const char *a[], T2 size)
{
	int lenMax=0, max=0;
	for(int i=0; i<size; i++)
	{
		int len = strlen(a[i]);
		if(len > lenMax)
		{
			lenMax = len;
			max = i;
		}
	}
	return a[max];
}

int main(int argc, char **argv)
{
	int a[] = {4,2,6,8,2,9};
	cout << maxn(a, 6) << endl;;

	float b[] = {1.3, 1.4, 1.7, 1.2, 1.9, 1.02};
	cout << maxn(b, 6) << endl;;

	const char *c[] = {"abc", "xy", "aa", "abcdef", "opop", ""};
	cout << maxn<int>(c, 6) << endl;;

	return 0;
}
