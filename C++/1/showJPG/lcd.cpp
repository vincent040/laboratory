#include "lcd.h"

LCD::LCD()
{
//    // 准备LCD屏幕
//    _fd = Open("/dev/fb0", O_RDWR|O_EXCL);

//    // 获取LCD设备的当前参数
//    _vinfo = (struct fb_var_screeninfo *)calloc(1,
//                        sizeof(struct fb_var_screeninfo));
//    ioctl(_fd, FBIOGET_VSCREENINFO, _vinfo);

//    // 根据当前LCD设备参数申请适当大小的FRAMEBUFFR
//    long bpp = _vinfo->bits_per_pixel;

//    _fbmem = (char *)mmap(NULL, _vinfo->xres * _vinfo->yres * bpp/8,
//                            PROT_READ|PROT_WRITE, MAP_SHARED, _fd, 0);
}

LCD::~LCD()
{
//    munmap(_fbmem, this->screenSize());
//    free(_vinfo);
//    close(_fd);
}

//u_int32_t LCD::screenSize() const
//{
//    return _vinfo->xres * _vinfo->yres * _vinfo->bits_per_pixel / 8;
//}

