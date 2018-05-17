#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#define BIGNUM 5000

void index_to_the_moon(int ary[]);

int main(int argc, char **argv)
{
    int intary[100];
    index_to_the_moon(intary);
	exit(EXIT_SUCCESS);
}

void index_to_the_moon(int ary[])
{
    int i;
    for(i=0; i<BIGNUM; i++)
    {
        ary[i] = i;
    }
}
