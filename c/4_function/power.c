#include <stdio.h>
#define EPSILON 3.4e-38

float my_exper(float base, int exp)
{
    int i;
    float tmp = base;
    for(i=0; i<exp-1; i++)
    {
        base *= tmp;
    }
    return base;
}

float my_exper2(float base, int exp)
{
    if(exp == 0)
        return 1;
    
    return my_exper2(base, exp-1) * base;
}


int main(void)
{
    printf("请输入底数和幂指数（例如：3.14, 2）代表求3.14的平方：");
    
    float base;
    int exp;
    scanf("%f, %d", &base, &exp); // 为了突出重点，此处未进行输入合法性检测，望读者知悉
    
    // 第一：0的0次方没有意义
    if(base == 0 && exp == 0)
        printf("0的0次方无意义！\n");
    
    // 第二：0的任意次方（0次方除外）均为0
    if(base == 0 && exp != 0)
        printf("%f^%d = 0\n", base, exp);
    
    // 第三：任意数（0除外）的0次方均为1
    else if(base != 0 && exp == 0)
        printf("%f^%d = 1\n", base, exp);
    
    // 第四：负整数次幂，转换为正次幂的倒数
    else if(exp < 0)
    {
        exp *= -1;
        printf("%f^%d = %.6f\n", base, exp, 1/my_exper(base, exp));
        printf("%f^%d = %.6f\n", base, exp, 1/my_exper2(base, exp));
    }
    
    // 第五：正整数次幂
    else
    {
        printf("%f^%d = %.6f\n", base, exp, my_exper(base, exp));
        printf("%f^%d = %.6f\n", base, exp, my_exper2(base, exp));
    }
    
    return 0;
}