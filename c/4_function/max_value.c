#include <stdio.h>

// 求出3个数中最大的一个
int max(int x, int y, int z)
{
    int max = (x>y) ? x : y;
    return (max>z) ? max : z;
}

int main(void)
{
    printf("请输入3个整数: ");
    
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c); // 为了突出重点，此处未进行输入合法性检测，望读者知悉
    
    printf("最大的数是: %d\n", max(a, b, c));
    return 0;
}



