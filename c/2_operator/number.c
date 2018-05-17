#include <stdio.h>
#include <limits.h>

int main(void)
{
	int begin;
	printf("pls input an integer: ");

	scanf("%d", &begin);
	int i;
	for(i=0; i<=10; i++)
	{
		printf("%d\t", begin + i);
	}
	printf("\n");
	return 0;
}
