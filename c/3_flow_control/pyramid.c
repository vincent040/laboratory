#include <stdio.h>
#include "myhead.h"

int main(void)
{
	printf("Pls input a latter: ");
	char ch;
	scanf("%c", &ch);
		
	if((ch<'A') || (ch>'Z'))
	{
		printf("we need a capital latter.\n");
		return 1;
	}

	char  line;
	line = ch - 'A' + 1;

	int i, j;
	for(i=1; i<=line; i++)
	{
		// print blank space
		for(j=0; j<line-i; j++)
		{
			printf(" ");
		}

		// print ascending letters
		for(j=0; j<i; j++)
		{
			printf("%c", 'A'+j);
		}

		// print descending letters
		for(j-=2; j>=0; j--)
		{
			printf("%c", 'A'+j);
		}
		printf("\n");
	}
	return 0;
}
