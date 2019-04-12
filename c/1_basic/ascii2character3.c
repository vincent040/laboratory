#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define __CHAR_SIGNED__ // enable the "signed char" version
#include <limits.h> // for CHAR_MIN and CHAR_MAX

#define SIZE 5

short calculate(char input[])
{
	short num=0;
	int len;
	len = strlen(input)-1;
	int pow = 1, i = 1;

	while(len-i > -1)
	{
		num += (input[len-i]-'0')*pow;
		pow *= 10;
		i++;
	}
	return num;
}

bool is_digit(const char *input)
{
	bool flag = true;
	int i=0, len=strlen(input)-1;

	while(i<len)
	{
		if(input[i]>'9' || input[i]<'0')
		{
			flag = false;
			break;
		}
		i++;
	}
	return flag;
}

bool more_then(const char input[], int limit)
{
	if(input[limit-1] != 0 && input[limit-1] != '\n')
		return true;

	return false;
}

int main(void)
{
	short num;
	static char input[SIZE];

	while(1)
	{
		memset(input, 0, SIZE);

		printf("pls input an ASCII value(0-127): ");
		fgets(input, SIZE, stdin);

		/*********** empty line ***********/
		if(input[0] == '\n')
			continue;

		/********** out of range **********/
		if(more_then(input, 4))
		{
			printf("invalid input!\n");
			while(getchar() != '\n');
			continue;
		}

		/********* NOT digits only *********/
		if(!is_digit(input))
		{
			printf("invalid input!\n");
			continue;
		}

		num = calculate(input); // the same as atoi()
		/********** out of range **********/
		if(num > CHAR_MAX || num < 0)
		{
			printf("out of range!\n");
			continue;
		}

		/*********************************** 
		Congratulations! no logical flaw was
		found, now jump out of this loop and
		print the answer.
		***********************************/
		break;
	}
	printf("character: '%c'\n", num);
	return 0;
}
