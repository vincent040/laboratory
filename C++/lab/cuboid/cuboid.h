#ifndef CUBOID_H
#define CUBOID_H

#include <iostream>
#include <string>

using namespace std;

class cuboid
{
private:
    // 常成员数据必须在初始化时显式地赋值
    const int _length;
    const int _width;
    const int _height;

    string _color;
    string *p;

public:
    cuboid(int l=0, int w=0, int h=0);

    int length(){return _length;}
    int width (){return _width; }
    int height(){return _height;}

    // const型成员方法保证不直接修改任何成员数据
    int volume() const;

    // const可以用来作为函数重载的依据
    string color();
    string color()const;
};

#endif // CUBOID_H
