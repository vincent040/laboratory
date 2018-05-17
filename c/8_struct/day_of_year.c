#include <stdio.h>

struct date
{
	short year;
	char month;
	char day;
};

int main(void)
{
	printf("pls input month, day and year" 
			" with this format:(1969/09/23) ");

	struct date sunny;
	if(scanf("%hu/%hhd/%hhd", &sunny.year, &sunny.month, \
			&sunny.day) != 3)
	{
		printf("all of them should be positive integers, Bye-bye!\n");
		return 1;
	}

	if(sunny.month<1 || sunny.month>12 || sunny.day<1 || sunny.day>31)
	{
		printf("invalid argument.\n");
		return 2;
	}
	if(((sunny.month%2 == 0) && (sunny.day > 31)) || \
		(sunny.month == 2 && sunny.day > 29))
	{
		printf("invalid argument.\n");
		return 2;
	}
 
	int month_leap[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int month_normal[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i, total_days = 0;

	if((sunny.year%4==0 && sunny.year%100!=0) || (sunny.year%400==0)) // leap year
	{
		for(i=0; i<sunny.month-1; i++)
		{
			total_days += month_leap[i];
		}
		total_days += sunny.day;
	}
	else
	{
		for(i=0; i<sunny.month-1; i++)
		{
			total_days += month_normal[i];
		}
		total_days += sunny.day;
	}

	printf("anwser: %d\n", total_days);

	return 0;
}
