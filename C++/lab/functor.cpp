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
// 描述: 函数对象、函数运算符
//
////////////////////////////////////////////////

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <time.h>
#include <list>
#include <cmath>

using namespace std;

// 函数模板
// 功能: 遍历 [begin, end) 的所有数据
//       并输出到屏幕
template <typename T>
void show(T begin, T end)
{
    while(begin != end)
    {
        cout << *begin << "\t";
        begin++;
    }
    cout << endl;
}

/*
************************************
            一元谓词
************************************
*/

// 奇数返回真，否则返回假
// 该函数的参数 --》 是调用者对象的元素的值
bool isOdd(const int &value)
{
    return value%2;
}

bool moreThan200(const int &value)
{
    return value>200;
}


// 定义一个类，重载函数运算符
class moreThan
{
private:
    int threshold;

public:
    moreThan(const int &value){threshold = value;}
    bool operator()(const int &i){return i>threshold;}
};

/*
************************************
            二元谓词
************************************
*/
bool same_integeral_part(double first, double second)
{
    return int(first) == int(second);
}

bool is_near(double first, double second)
{
    return abs(first-second) < 0.5;
}


class isNear
{
private:
    float Dvalue;
public:
    isNear(double d){Dvalue = d;}

    bool operator()(double first, double second);
};

bool isNear::operator ()(double first, double second)
{
    return abs(first - second) < Dvalue;
}


int main(void)
{
    list<int> numbers;
    srand(time(NULL));

    // 产生一些随机数，放进list中
    int count=0;
    while(count <= 8)
    {
        numbers.push_back(rand() % 1000);
        count++;
    }

    // 显示这些随机数
    cout << "原始数据: " << endl;
    show(numbers.begin(), numbers.end());
    cout << endl;

    // 1，删除所有的奇数
    // 函数 isOdd 只有一个参数：
    numbers.remove_if(isOdd);

    // 显示这些随机数
    cout << "删掉奇数后: " << endl;
    show(numbers.begin(), numbers.end());
    cout << endl;

    /*
     ************************************
     一元谓词:
     ① 函数指针
     ② 函数对象
     ************************************
    */

    // ① 使用函数指针回调，函数内涵固定
    cout << "删掉超过200的数字: " << endl;
    numbers.remove_if(moreThan200);
    show(numbers.begin(), numbers.end());
    cout << endl;


    // ② 使用函数对象，函数内涵可变
    int threshold;
    cout << "请输入最小数值阀值: " << endl;
    cin >> threshold;

    cout << "删掉超过" << threshold << "的数字: " << endl;
    numbers.remove_if(moreThan(threshold));
    show(numbers.begin(), numbers.end());
    cout << endl;

    /*
     ************************************
                二元谓词
     ************************************
    */

    double a[10] = {1.1, 1.7, 1.1, 7.9, 2.0,
                    6.2, 8.1, 2.3, 2.6, 1.1};
    list<double> digits(a, a+10);

    cout << "======== 原始数据 ========" << endl;
    show(digits.begin(), digits.end());

    digits.sort();
    digits.unique();
    cout << "======== 排序并删除重复数据后 ========" << endl;
    show(digits.begin(), digits.end());


//    digits.unique(same_integeral_part);
//    cout << "======== 删掉相同整数部分后 ========" << endl;
//    show(digits.begin(), digits.end());

//    digits.unique(is_near);
//    cout << "======== 删掉足够接近的数据后 ========" << endl;
//    show(digits.begin(), digits.end());

    digits.unique(isNear(0.9));
    cout << "======== 删掉足够接近的数据后 ========" << endl;
    show(digits.begin(), digits.end());

    return 0;
}
