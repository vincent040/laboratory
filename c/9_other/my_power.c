#include <stdio.h>
#include <errno.h>
#include <limits.h>

#define EPSINON 1e-38

float my_power(float num, int pow)
{
	switch(pow)
	{
		case 0:
			return 1;
		case 1:
			return num;
		case INT_MIN ... -1:
			num *= -1;
		case 2 ... INT_MAX:
			num *= my_power(num, pow-1);
			break;
	}

	return num;
}

int main(void)
{
	float num;
	int pow;
	printf("Pls input the base and power number(e.g. 3.14, 2):");

	while(scanf("%f,%d", &num, &pow) != 2 ||
		getchar() != '\n')
	{
		while(getchar() != '\n');

		printf("input invalid!\n");
		printf("Pls input the base and power number(e.g. 3.14, 2):");
	}

	if(num>-EPSINON && num<EPSINON) //-EPSINON < num < EPSINON
	{
		if(pow == 0) //forbiden!
			printf("forbiden!\n");
		else
			printf("answer: 0\n");
	}
	else
	{
		if(pow > 0)
			printf("answer: %.6f\n", my_power(num, pow));
		else if(pow == 0)
			printf("answer: 1\n");
		else
		{
			pow *= -1;
			printf("answer: %.6f\n", 1/my_power(num, pow));
		}
	}
	return 0;
}
