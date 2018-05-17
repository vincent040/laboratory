#include <stdio.h>

int main(void)
{
    printf("请输入一个整数：");
    
    int max;
    scanf("%d", &max); // 为了突出重点，此处未进行输入合法性检测，望读者知悉
    
    int dollars;
    for(dollars=1; dollars<=max; dollars++)
    {
        int j;
        for(j=0; j<dollars; j++)
        {
            printf("$");
        }
        
        printf("\n");
    }
    
    return 0;
}
