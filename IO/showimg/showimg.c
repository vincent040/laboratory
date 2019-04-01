#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <dlfcn.h>

#include "bmp.h"

char *init_lcd(struct fb_var_screeninfo *vinfo)
{
	int lcd = open("/dev/fb0", O_RDWR);

	ioctl(lcd, FBIOGET_VSCREENINFO, vinfo);
	int bpp = vinfo->bits_per_pixel;
	int screensize = vinfo->xres * vinfo->yres * bpp/8;

	char *fbmem = mmap(NULL, screensize, PROT_READ|PROT_WRITE,
			   MAP_SHARED, lcd, 0);
	if(fbmem == MAP_FAILED)
	{
		perror("映射显存失败");
		exit(0);
	}
	return fbmem;
}

void usage(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("参数不对\n");
		exit(0);
	}
}

int main(int argc, char **argv) // ./showimg [image]
{
	usage(argc, argv);

	char *lib;
	if(strstr(argv[1], ".bmp"))
		lib = "libbmp.so";
	if(strstr(argv[1], ".jpg"))
		lib = "libjpg.so";

	void *handle = dlopen(lib, RTLD_NOW);
	if(handle == NULL)
	{
		perror("打开动态库失败");	
		exit(0);
	}

	void (*display)(char *imgfile, char *fbmem,
			struct fb_var_screeninfo *vinfo,
			int xoffset, int yoffset);
	display = dlsym(handle, "display");
	if(display == NULL)
	{
		perror("查找符号失败");
		exit(0);
	}

	struct fb_var_screeninfo vinfo;
	bzero(&vinfo, sizeof(vinfo));
	char *fbmem = init_lcd(&vinfo);

	display(argv[1], fbmem, &vinfo, 0, 0);

	return 0;
}
