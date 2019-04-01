////////////////////////////////////////////////////
//
//  Copyright(C), 广州粤嵌通信科技股份有限公司
//
//  作者: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
//  文件: lab/C++/4_derive_inherit/line/line.h
//  描述: line类设计
//
////////////////////////////////////////////////////

#ifndef LINE_H
#define LINE_H

#include "point.h"

class line
{
private:
    // 包含两个类对象，这是一种经典的"has-a"（复合）关系
    point p1;
    point p2;

public:
    line();
    line(point p1, point p2);

    // 获取线段长度
    double length() const;
};

#endif // LINE_H
