#include "myhead.h"

int main(void)
{
	printf("before exec()\n");

	//execl("/bin/ls", "ls", "-l", NULL);
	execlp("ls", "ls", "-l", NULL);

/*
	char *a[] = {"ls", "-l", NULL};
	execv("ls", a);
*/

	printf("after exec()\n");
}
