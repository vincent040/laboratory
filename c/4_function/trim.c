#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

char *trim(char *s)
{
    // 找到字符串中的第一个空格
    int i;
    for(i=0; s[i]!='\0' && s[i]!=' '; i++);
    
    // 如果不含空格，则直接返回
    if(s[i] == '\0')
        return s;
    
    // 将后续的非空格字符往前移
    int j;
    for(j=i+1; s[j]!='\0'; j++)
    {
        if(s[j] != ' ')
        {
            s[i] = s[j];
            i++;
        }
    }
    s[i] = '\0';
    
    return s;
}


int main(int argc, char **argv)
{
    char s[100];
    
    while(1)
    {
        bzero(s, 100);
        fgets(s, 100, stdin);
        
        printf("after trimed: %s", trim(s));
    }
    
    return 0;
}​



