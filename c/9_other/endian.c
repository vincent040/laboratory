#include <stdio.h>

int little_endian(char ch)
{
	if(ch == 0x78)
		return 1; //little endian
	else
		return 0; //big endian
}

int main(void)
{
	int i=0x12345678;
	char *p = (char *)&i;

	if(little_endian(*p) == 1)
	{
		printf("little endian.\n");
	}
	else{
		printf("big endian.\n");
	}
	return 0;
}
