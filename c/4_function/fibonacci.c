#include <stdio.h>

int fibonacci(int num)
{
    // 第1和第2个斐波那契数不需要经过任何计算，规定都是1
    if(num == 1 || num == 2)
        return 1;
    
    // 第N个斐波那契数，等于第N-1个和第N-2个斐波那契数之和
    return (fibonacci(num-1) + fibonacci(num-2));
}


int main(void)
{
    printf("你想看第几个斐波那契数？");
    
    int num;
    scanf("%d", &num); // 为了突出重点，此处未进行输入合法性检测，望读者知悉
    
    printf("第 %d 个斐波那契数是: %d\n", num, fibonacci(num));
    return 0;
}