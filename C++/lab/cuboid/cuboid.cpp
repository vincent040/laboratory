#include "cuboid.h"

// 常成员数据必须在初始化时显式地赋值
cuboid::cuboid(int l, int w, int h):_length(l), _width(w), _height(h)
{
    _length = 200;
    _color = "red";
    p = &_color;
}

int cuboid::volume() const
{
    // 在const成员函数中修改类成员将会报错
    // _color = "blue";
    return _length * _width * _height;
}

string cuboid::color()
{
    _color = "black";
    return _color;
}

string cuboid::color() const
{
    // const型常成员函数保证“不直接”修改成员数据
    // 但却可以通过指针修改成员数据
    *p = "yellow";
    return _color;
}
