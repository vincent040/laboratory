#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	FILE *fp;
	fp = fopen("apple", "w");

	fclose(fp);
	return 0;
}
