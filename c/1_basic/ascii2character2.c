#include <stdio.h>
#include <limits.h> // for CHAR_MIN and CHAR_MAX

int main(void)
{
	short ch;

	printf("pls input an ASCII value(0-127): ");
	int ret1, ret2;

	while((ret1=scanf("%hd", &ch)) != 1 || // input doesn't match the format
		ch>127 || ch<0 || // input out of range
		(ret2=getchar()) != '\n') // input doesn't match the format
	{
		if(ret1!=1 || ret2!='\n')
			while(getchar() != '\n'); // discards invalid inputs

		printf("input invalid!\n");
		printf("pls input an ASCII value(0-127): ");
	}

	printf("the character of %d is '%c'\n", ch, (char)ch);

	return 0;
}
