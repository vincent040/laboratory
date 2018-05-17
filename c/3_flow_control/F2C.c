#include <stdio.h>

int main(void)
{
	float fah, cel; //Fahrenheit and Celsius;
	printf("pls input the temperature you wanna calculate: ");

	while(scanf("%f", &fah) != 1 || getchar() != '\n')
	{
		while(getchar() != '\n'); // discards invalid inputs

		printf("input invalid!\n");
		printf("pls input the temperature you wanna calculate: ");
	}

	cel = (5*(fah-32)) / 9;
	printf("It equals %5.2f\n", cel);
	return 0;
}
