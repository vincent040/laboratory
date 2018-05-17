#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	FILE *fp_from, *fp_to;

	if(argc != 3){
		fprintf(stderr, "Uage: %s <file_src> <file_dest>", argv[0]);
		exit(-1);
	}
	
	/******************************
	   open two files for copying
	*******************************/
	if((fp_from=fopen(argv[1], "r+")) == NULL){
		fprintf(stderr, "fopen %s fail: %s\n", argv[1], strerror(errno));
		exit(-1);
	} 
	if((fp_to=fopen(argv[2], "w+")) == NULL){
		fprintf(stderr, "fopen %s fail: %s\n", argv[2], strerror(errno));
		exit(-1);
	} 

	int ret_fgetc, ret_fputc;

	while(1){

		ret_fgetc = fgetc(fp_from);

		/******************************
		   if the return value is EOF
		*******************************/
		if((ret_fgetc == EOF) && (ferror(fp_from)) && (errno == EINTR))
			continue;

		else if((ret_fgetc == EOF) && (ferror(fp_from)) && (errno != EINTR)){
			perror("fgetc failed");
			exit(-1);
		}

		else if((ret_fgetc == EOF) && (feof(fp_from)))
			break;

		/**********************************
		   if the return value is NOT EOF
		***********************************/
		else{
			while(1){
				ret_fputc = fputc(ret_fgetc, fp_to);

				if((ret_fputc == EOF) && (errno == EINTR))
					continue;

				else if((ret_fputc == EOF) && (errno != EINTR)){
					perror("fputc failed");
					exit(-2);
				}

				break;
			}
		}

	}
	fclose(fp_from);
	fclose(fp_to);

	return 0;
}
