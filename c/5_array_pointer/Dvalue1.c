#include <stdio.h>

#define SIZE 5

double Dvalue(double da[])
{
	int i;
	double max, min;
	max = min = da[0];

	for(i=1; i<SIZE; i++)
	{
		max = (max>da[i]) ? max : da[i];
		min = (min<da[i]) ? min : da[i];
	}
	return (max - min);
}

int main(void)
{
	double da[SIZE] = {2.3, -1.54, 9.1, 5.88, -0.2};
	printf("D-value: %lf\n", Dvalue(da));

	return 0;
}
