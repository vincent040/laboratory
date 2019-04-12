#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>

#include "myhead.h"

int main(void)
{
	int minutes;
	static char input[SIZE];

	while(1){
		memset(input, 0, SIZE);

		/**********************************
			USHRT_MAX = 65,535
		**********************************/
		printf("minutes (0 ~ %hu): ", USHRT_MAX);
		if(!s_fgets(input, SIZE, stdin))
			perror_exit("fgets failed");

		/********** empty line ************/
		if(input[0] == '\n')
			continue;

		/********** out of range **********/
		if(more_then(input, 6)){
			printf("invalid input!\n");
			while(getchar() != '\n');
			continue;
		}

		/********* NOT digits only *********/
		if(!is_digit(input)){
			printf("invalid input!\n");
			continue;
		}

		minutes = atoi(input);
		/********** out of range **********/
		if((minutes > USHRT_MAX) || (minutes < 0)){
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

	printf("%d hours and %d minutes\n",
		(minutes/MIN_PER_HOUR), (minutes%MIN_PER_HOUR));
	return 0;
}
