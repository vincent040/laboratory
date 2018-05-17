#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define BUFSIZE 64

static int line_num = 0;

FILE *Fopen(const char *path, const char *mode)
{
	FILE *fp;
	fp = fopen(path, mode);

	if(fp == NULL)
		perror("fopen error");

	return fp;
}

int main(int argc, char **argv)
{
	FILE *fp = NULL;
	FILE *fpline = NULL;

	if(access("line", F_OK))
		fpline = Fopen("line", "w+");

	else{
		/*
		** open the file "line" without 
		** overwrite its content.
		*/
		fpline = Fopen("line", "r");

		fread(&line_num, sizeof(int), 1, fpline);

		// open the file "line" with mode "w+"
		freopen("line", "w+", fpline);
	}
	setvbuf(fpline, NULL, _IONBF, 0);


	/*
	** fopen the file "times2" with mode "a+"
	** then it can be created when it is not
	** exist and won't be overwrited when it
	** does exist.
	*/
	fp = Fopen("times", "a+");

	setvbuf(fp, NULL, _IONBF, 0);

	char num_str[BUFSIZE]; 

	time_t *tloc=(time_t *)malloc(sizeof(time_t));


	// obtain system time every 1s in this non-ending loop
	while(1){

		snprintf(num_str, BUFSIZE, "%d\t", ++line_num);

		time(tloc);
		snprintf(num_str+strlen(num_str)-1, BUFSIZE, "\t%s", ctime(tloc));
		fputs(num_str, fp);

		rewind(fpline);
		fwrite(&line_num, sizeof(int), 1, fpline);


		fputs(num_str, stdout);

		sleep(1);
	}

	return 0;
}
