#include <iostream>
#include "bmp.h"

using namespace std;

int main(void)
{
    BMP *a = new BMP("1.bmp");

    a->showName();
    a->showInfo();

    cout << "图片大小：" << a->totalsize() << "(字节)" << endl;


    cout << endl << "复制这张图片到另一个对象中" << endl;
    BMP b;
    b = *a;

    cout << "删除原来的图片对象..." << endl;
    delete a;

    cout << endl << "显示复制品的相关信息：" << endl;
    b.showName();
    b.showInfo();

    cout << "图片大小：" << b.totalsize() << "(字节)" << endl;

    return 0;
}

