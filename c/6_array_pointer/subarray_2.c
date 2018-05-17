#include <stdio.h>

#define LIM 128

int main(void)
{
	int a[LIM];
	int len = 0;
	printf("pls input some"
		" integers('#' to terminate): ");

	while(scanf("%d", &a[len]) != 0)
		len++;

	int max=a[0], sum=0;

	int i;
	for(i=0; i<len; i++)
	{
		sum += a[i];

		if(sum > max)
			max = sum;

		else if(sum < 0)
			sum = 0;
	}

	printf("max sub-array's sum: %d\n", max);
	return 0;
}
