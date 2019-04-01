#include <stdio.h>
#include <string.h>

#define LIM 16

char *my_strcat(char *str1, char *str2)
{
	int i;
	i = strlen(str1); //str1[i] point to the '\0'

	int j;
	for(j=0; j<LIM-i; j++)
	{
		str1[j+i] = str2[j];
	}
	return str1;
}

int main(void)
{
	char str1[LIM] = "hello";
	char str2[LIM] = "123456789012345";

	printf("strings combined: %s\n", my_strcat(str1, str2));
	return 0;
}
