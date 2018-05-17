#include <stdio.h>

#define SIZE 5

double Dvalue(double data[], int size)
{
	int i;
	double max, min;

	if(size < 1)
		return 0;

	if(data[0] > data[1])
	{
		max = data[0];
		min = data[1];
	}
	else
	{
		min = data[0];
		max = data[1];
	}

	for(i=2; i+1<size; i+=2)
	{

		if(data[i] > data[i+1])
		{
			if(data[i] > max)
				max = data[i];

			if(data[i+1] < min)
				min = data[i+1];
		}
		else
		{
			if(data[i+1] > max)
				max = data[i+1];

			if(data[i] < min)
				min = data[i];
		}

	}

	if((i+1 == size) && (data[i] > max))
		max = data[i];

	if((i+1 == size) && (data[i] < min))
		min = data[i];

	return (max - min);
}

int main(void)
{
	double data[SIZE] = {2.3, -1.54, 9.1, 5.88, -3.2};
	printf("D-value: %lf\n", Dvalue(data, SIZE));

	return 0;
}
