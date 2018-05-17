#include "wrap.h"

// 将bmp_buffer中的24bits的RGB数据，写入LCD的32bits的显存中
void write_lcd(char *rgb, struct image_info *imageinfo,
            char *fbmem, struct fb_var_screeninfo *vinfo)
{
    bzero(fbmem, vinfo->xres * vinfo->yres * 4);

    u_int32_t x, y;
	for(x=0; x<vinfo->yres && x<imageinfo->height; x++)
	{
		for(y=0; y<vinfo->xres && y<imageinfo->width; y++)
		{
            u_int32_t lcd_offset = (vinfo->xres*x + y) * 4;
            u_int32_t bmp_offset = (imageinfo->width*x+y) *
						    imageinfo->pixel_size;

            memcpy(fbmem + lcd_offset + vinfo->red.offset/8,
                   rgb + bmp_offset + 0, 1);
            memcpy(fbmem + lcd_offset + vinfo->green.offset/8,
                   rgb + bmp_offset + 1, 1);
            memcpy(fbmem + lcd_offset + vinfo->blue.offset/8,
                   rgb + bmp_offset + 2, 1);
		}
	}
}

// 将jpeg文件的压缩图像数据读出，放到jpg_buffer中去等待解压
unsigned long read_image_from_file(int fd,
                   char *jpg_buffer,
                   long jpg_size)
{
	unsigned long nread = 0;
	unsigned long total = 0;

	while(jpg_size > 0)
	{
		nread = read(fd, jpg_buffer, jpg_size);

		jpg_size -= nread;
		jpg_buffer += nread;
		total += nread;
	}
	close(fd);

	return total;
}

int Stat(const char *filename, struct stat *file_info)
{
	int ret = stat(filename, file_info);

	if(ret == -1)
	{
		fprintf(stderr, "[%d]: stat failed: "
			"%s\n", __LINE__, strerror(errno));
		exit(1);
	}

	return ret;
}

int Open(const char *filename, int mode)
{
	int fd = open(filename, mode);
	if(fd == -1)
	{
		fprintf(stderr, "[%d]: open failed: "
			"%s\n", __LINE__, strerror(errno));
		exit(1);
	}

	return fd;
}


/**
 * 将jpg指向的图像解码到*rgb指向的内存中
 * 其中rgb指向由调用者提供的一级指针
 */
bool decompress_jpg(char *jpgfile, char **rgb, struct image_info *imginfo)
{
    assert(jpgfile);
	assert(rgb);
    assert(imginfo);

	// 读取图片文件属性信息
	// 并根据其大小分配内存缓冲区jpg_buffer
	struct stat file_info;
	Stat(jpgfile, &file_info);
	int fd = Open(jpgfile, O_RDONLY);

	char *jpg_buffer;
	jpg_buffer = (char *)calloc(1, file_info.st_size);
	read_image_from_file(fd, jpg_buffer, file_info.st_size);

	// 声明解压缩结构体，以及错误管理结构体
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	// 使用缺省的出错处理来初始化解压缩结构体
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	// 配置该cinfo，使其从jpg_buffer中读取jpg_size个字节
	// 这些数据必须是完整的JPEG数据
    jpeg_mem_src(&cinfo, (unsigned char *)jpg_buffer, file_info.st_size);

	// 读取JPEG文件的头，并判断其格式是否合法
	int ret = jpeg_read_header(&cinfo, true);
	if(ret != 1)
	{
        fprintf(stderr, "不是jpg图片，你逗我？[%s]\n", strerror(errno));
        return false;
	}

	// 开始解压
	jpeg_start_decompress(&cinfo);

    imginfo->width = cinfo.output_width;
    imginfo->height = cinfo.output_height;
    imginfo->pixel_size = cinfo.output_components;

    int row_stride = imginfo->width * imginfo->pixel_size;

	// 根据图片的尺寸大小，分配一块相应的内存rgb
	// 用来存放从jpg_buffer解压出来的图像数据
    long rgb_size = imginfo->width *
                 imginfo->height *
                 imginfo->pixel_size;
	*rgb = (char *)calloc(1, rgb_size);

	// 循环地将图片的每一行读出并解压到bmp_buffer中
	while(cinfo.output_scanline < cinfo.output_height)
	{
		unsigned char *buffer_array[1];
        buffer_array[0] = *(unsigned char **)rgb +
				(cinfo.output_scanline) * row_stride;
		jpeg_read_scanlines(&cinfo, buffer_array, 1);
	}

	// 解压完了，将jpeg相关的资源释放掉
 	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(jpg_buffer);

    return true;
}

bool lcd_init(struct fb_var_screeninfo *vinfo, char **fbmem)
{
	assert(vinfo);

	// 准备LCD屏幕
	int lcd = Open("/dev/fb0", O_RDWR|O_EXCL);

	// 获取LCD设备的当前参数
	ioctl(lcd, FBIOGET_VSCREENINFO, vinfo);

	// 根据当前LCD设备参数申请适当大小的FRAMEBUFFR
    long bpp = vinfo->bits_per_pixel;
    *fbmem = mmap(NULL, vinfo->xres * vinfo->yres * bpp/8,
			PROT_READ|PROT_WRITE, MAP_SHARED, lcd, 0);
	if(*fbmem == MAP_FAILED)
	{
		perror("mmap() failed");
        return false;
	}

    return true;
}
