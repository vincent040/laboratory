#include <stdio.h>

#define DAYS_PER_WEEK 7

int main(void)
{
	int days;
	printf("how many days do you wanna calculater: ");

	int ret1, ret2;
	while((ret1=scanf("%d", &days)) != 1 || // input don't match the format
			days <0 || // out of range
			(ret2=getchar()) != '\n') // invalid input
	{
		if(ret1 != 1 || ret2 != '\n')
			while(getchar() != '\n'); // discards invalid inputs

		printf("input invalid!\n");
		printf("how many days do you wanna calculater: ");
	}

	printf("%d days are %d weeks, %d days\n", \
		days, days / DAYS_PER_WEEK, days % DAYS_PER_WEEK);
	return 0;
}
