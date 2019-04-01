#include <stdio.h>

#define SECS 365*24*3600UL // makes SECS compatible

int main(void)
{
	printf("seconds per year: %lu\n", SECS);
	return 0;
}
