#include <stdio.h>
#include <ctype.h>

#define STOP '#'

int main(void)
{
	int c;
	int n_spaces = 0;
	int n_lines = 0;
	int n_characters = 0;

	printf("Enter text to be analyzed"
	       "(# to terminate):\n");

	while((c=getchar()) != STOP)
	{
		switch(c)
		{
			case ' ':
				n_spaces++;
				break;
			case '\n':
				n_lines++;
				break;
			default:
				n_characters++;
		}
	}

	printf("spaces = %d, lines = %d,"
		"characters = %d\n", \
		n_spaces, n_lines, n_characters);
	return 0;
}
