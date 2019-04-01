#include <stdio.h>

#define WATER_MOLCULER 3.0e-23

int main(void)
{
	long double water_molculers;
	float quota;
	printf("how many quarts of the water: ");

	int ret1, ret2;
	while((ret1=scanf("%f", &quota) != 1) || // don't match the format
		quota < 0 || // invalid input
		(ret2=getchar()) != '\n') // don't match the format
	{
		if(ret1 != 1 || ret2 != '\n')
			while(getchar() != '\n'); // discards invalid inputs

		printf("input invalid!\n");
		printf("how many quarts of the water: ");
	}

	water_molculers = (quota*950) / WATER_MOLCULER;
	printf("awesome! you've got %Le water molecules!\n", \
				water_molculers);

	return 0;
}
