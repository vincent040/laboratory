#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	fprintf(stdout, "to stdout ... ");
	fprintf(stderr, "to stderr ... ");

	_exit(0);
}
