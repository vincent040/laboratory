#ifndef BMP_H
#define BMP_H

#include <string>
#include "cbmp.h"

using std::string;

class BMP
{
public:
    BMP();
    BMP(const char *bmpfile);
    ~BMP();

    void showName(); // 名字
    void showInfo(); // 尺寸
    int  totalsize(); // 图片总大小


    BMP &operator=(const BMP &rh);

private:
    char *rgb;
    string name;
    struct image_info _info;
};

#endif // BMP_H
