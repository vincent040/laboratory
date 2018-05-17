#include "jpg.h"

// 将jpeg文件的压缩图像数据读出，放到jpg_buffer中去等待解压
unsigned long read_image_from_file(int fd,
				   unsigned char *jpg_buffer,
				   unsigned long jpg_size)
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

void display(char *jpgfile, char *fbmem,
	     struct fb_var_screeninfo *vinfo,
	     int xoffset, int yoffset)
{
	// 读取图片文件属性信息
	// 并根据其大小分配内存缓冲区jpg_buffer
	struct stat file_info;
	Stat(jpgfile, &file_info);
	int fd = Open(jpgfile, O_RDONLY);

	unsigned char *jpg_buffer;
	jpg_buffer = (unsigned char *)calloc(1, file_info.st_size);
	read_image_from_file(fd, jpg_buffer, file_info.st_size);


	// 声明解压缩结构体，以及错误管理结构体
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	// 使用缺省的出错处理来初始化解压缩结构体
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	// 配置该cinfo，使其从jpg_buffer中读取jpg_size个字节
	// 这些数据必须是完整的JPEG数据
	jpeg_mem_src(&cinfo, jpg_buffer, file_info.st_size);


	// 读取JPEG文件的头，并判断其格式是否合法
	int ret = jpeg_read_header(&cinfo, true);
	if(ret != 1)
	{
		fprintf(stderr, "[%d]: jpeg_read_header failed: "
			"%s\n", __LINE__, strerror(errno));
		exit(1);
	}

	// 开始解压
	jpeg_start_decompress(&cinfo);

	struct image_info imageinfo;
	imageinfo.width = cinfo.output_width;
	imageinfo.height = cinfo.output_height;
	imageinfo.pixel_size = cinfo.output_components;

	int row_stride = imageinfo.width * imageinfo.pixel_size;

	// 根据图片的尺寸大小，分配一块相应的内存rgb_buffer
	// 用来存放从jpg_buffer解压出来的图像数据
	unsigned long rgb_size;
	unsigned char *rgb_buffer;
	rgb_size = imageinfo.width *
			imageinfo.height * imageinfo.pixel_size;
	rgb_buffer = (unsigned char *)calloc(1, rgb_size);

	// 循环地将图片的每一行读出并解压到rgb_buffer中
	int line = 0;
	while(cinfo.output_scanline < cinfo.output_height)
	{
		unsigned char *buffer_array[1];
		buffer_array[0] = rgb_buffer +
				(cinfo.output_scanline) * row_stride;
		jpeg_read_scanlines(&cinfo, buffer_array, 1);
	}

	// 解压完了，将jpeg相关的资源释放掉
 	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(jpg_buffer);

	// 清屏
	bzero(fbmem, vinfo->xres * vinfo->yres * 4);

	// 将rgb_buffer中的RGB图像数据，写入LCD的FRAMEBUFFER中
	char *tmp = fbmem;
	tmp += (yoffset*vinfo->xres + xoffset) * vinfo->bits_per_pixel/8;

	int lcd_w = vinfo->xres - xoffset;
	int lcd_h = vinfo->yres - yoffset;

	int row, column;
	for(row=0; row<lcd_h && row<imageinfo.height; row++)
	{
		for(column=0; column<lcd_w && column<imageinfo.width; column++)
		{
			unsigned long lcd_offset = (vinfo->xres*row + column) * 4;
			unsigned long rgb_offset = (imageinfo.width*row+column) *
						    imageinfo.pixel_size;

			memcpy(tmp + lcd_offset + vinfo->red.offset/8,
			       rgb_buffer + rgb_offset + 0, 1);
			memcpy(tmp + lcd_offset + vinfo->green.offset/8,
			       rgb_buffer + rgb_offset + 1, 1);
			memcpy(tmp + lcd_offset + vinfo->blue.offset/8,
			       rgb_buffer + rgb_offset + 2, 1);
		}
	}

	// 释放相关资源
	free(rgb_buffer);
	close(fd);
}
