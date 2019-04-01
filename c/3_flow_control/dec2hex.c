#include <stdio.h>
#include <stdbool.h>


int main(void)
{
    int decimal;
    bool negative = false;
    
    printf("请输入一个十进制数: ");
    scanf("%d", &decimal); // 为了突出重点，此处未进行输入合法性检测，望读者知悉
    
    // 判断并记录要转换的十进制数的正负号
    if(decimal < 0)
    {
        negative = true;
        decimal *= -1;
    }
    
    // 将该十进制数对16进行短除法，并将余数依次存入数组num中
    int i, num[10];
    for(i=0; i<10 && decimal!=0; i++)
    {
        num[i] = decimal%16;
        decimal /= 16;
    }
    
    printf("转换成十六进制为: %c0x", negative?'-':' ');
    
    // 将数组num中的数字倒序输出
    int j;
    for(j=i; j>0; j--)
    {
        switch(num[j-1])
        {
            case 10:
                printf("a");
                break;
            case 11:
                printf("b");
                break;
            case 12:
                printf("c");
                break;
            case 13:
                printf("d");
                break;
            case 14:
                printf("e");
                break;
            case 15:
                printf("f");
                break;
            default:
                printf("%d", num[j-1]);
                break;
        } //switch
    } //for
    
    printf("\n");
    return 0;
}
