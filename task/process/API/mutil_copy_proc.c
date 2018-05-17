#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void usage(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("Usage: %s <SRC> <DST>\n", argv[0]);
		exit(0);
	}
}

int main(int argc, char **argv)
{
	usage(argc, argv);

	pid_t pid;
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen(argv[2], "w");
	int i;

	
	unsigned long len = fseek(fp1, 0L, SEEK_END);
	rewind(fp1);

	pid = fork();

	// parent copy the top-halves
	if(pid > 0)
	{

		for(i=0; i<len/2; i++)
			fputc(fgetc(fp1), fp2);

		fclose(fp1);
		fclose(fp2);
	}

	// child copy the bottom-halves
	else if(pid == 0)
	{
		fseek(fp1, len/2, SEEK_SET);
		fseek(fp2, len/2, SEEK_SET);
		int c;
		while(1)
		{
			c = fgetc(fp1);
			if(c == EOF && feof(fp1))
				break;

			fputc(c, fp2);
		}
		fclose(fp1);
		fclose(fp2);
	}

	return 0;
}
