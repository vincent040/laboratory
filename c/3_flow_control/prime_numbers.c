#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

bool prime(int num)
{
	int i;
	for(i=2; i*i<(num+1); i++)
	{
		if(num%i == 0)
			return false;
		else
			continue;
	}
	return true;
}

int main(void)
{
	int boundary;
	printf("Input the boudary(between 0 and %d):", INT_MAX-1);

	int ret1, ret2;
	while((ret1=scanf("%d", &boundary)) != 1 || // input don't match the format
			boundary<0 || boundary>INT_MAX-1 || // out of range
			(ret2=getchar()) != '\n') // don't match the format
	{
		if(ret1!=1 || ret2!='\n') // discards invalid inputs
			while(getchar() != '\n');

		printf("invalid input!\n");
		printf("Input the boudary(between 0 and %d):", INT_MAX-1);
	}

	int num;
	for(num=2; num < boundary+1; num++)
	{
		if(prime(num))
			printf("%d\t", num);
	}
	printf("\n");

	return 0;
}
