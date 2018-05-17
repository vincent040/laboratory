///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/1_c2c++/show_jpeg/main.cpp
// 日期：2017-10
// 描述：C/C++混合编程范例，实现开发板刷jpg图片
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#include <iostream>
#include "lcd.h"
#include "wrap.h"

using namespace std;

void usage(int argc, char **argv)
{
    if(argc != 2)
    {
        cout << "用法：%s <JPG/JPEG格式图片>" << argv[0] << endl;
        exit(0);
    }
}

int main(int argc, char **argv)
{
//    usage(argc, argv);

//    LCD lcd;

//    // 解码并显示JPG图片
//    char *rgb = NULL;
//    struct image_info imginfo;
//    decompress_jpg(argv[1], &rgb, &imginfo);
//    write_lcd(rgb, &imginfo, lcd.fbmem(), lcd.screenInfo());

    return 0;
}

