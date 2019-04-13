#include "bmp.h"

#include <iostream>
#include <fstream>

using namespace std;

BMP::BMP()
{

}

BMP::BMP(const char *file)
{
    name = file;

    ifstream bmp(name.c_str());

    if(!bmp.is_open())
        abort();

    // 读取格式头
    bitmap_header head;
    bitmap_info   info;
    bmp.read((char *)(&head), sizeof(head));
    bmp.read((char *)(&info), sizeof(info));

    // 根据信息分配内存
    this->_info.width = info.width;
    this->_info.height= info.height;
    this->_info.pixel_size = info.bit_count/8;

    int size = info.width * info.height * info.bit_count/8;

    rgb = (char *)malloc(size);
    if(rgb == NULL)
        abort();

    // 将RGB数据读入缓冲区中
    bmp.read(rgb, size);
}

BMP::BMP(const BMP &r)
{
    name = r.name;
    _info = r._info;

    int size = _info.height * _info.width * _info.pixel_size;
    rgb = (char *)malloc(size);
    if(rgb == NULL)
        abort();

    // 深拷贝
    memcpy(rgb, r.rgb, size);
}

BMP::~BMP()
{
    free(rgb);
}

void BMP::showName()
{
    cout << "名字：" << name << endl;
}

void BMP::showInfo()
{
    cout << "宽：" << _info.width  << endl;
    cout << "高：" << _info.height << endl;
    cout << "深：" << _info.pixel_size << "（字节）" << endl;
}


int BMP::totalsize()
{
    return _info.width * _info.height * _info.pixel_size/8;
}

BMP &BMP::operator=(const BMP &rh)
{
    if(this == &rh)
        return *this;

    name = rh.name;
    _info = rh._info;

    int size = _info.height * _info.width * _info.pixel_size;
    rgb = (char *)malloc(size);
    if(rgb == NULL)
        abort();

    // 深拷贝
    memcpy(rgb, rh.rgb, size);
    return *this;
}
