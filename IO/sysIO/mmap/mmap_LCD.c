#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/input.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(void)
{
	int lcd = open("/dev/fb0", O_RDWR|O_EXCL);

	char *p_lcd;
	p_lcd = mmap(NULL, 800*480*4,
		PROT_READ|PROT_WRITE, MAP_SHARED, lcd, 0);

	unsigned x = 0xFFFFFFFF;
	int i;
	for(i=0; i< 800*480;i++)
	{
		memcpy(p_lcd+(4*i), &x, 4);
	}

	return 0;
}
