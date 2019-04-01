////////////////////////////////////////////////////
//
//  Copyright(C), 广州粤嵌通信科技股份有限公司
//
//  作者: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
//  文件: lab/C++/4_derive_inherit/line/point.h
//  描述: point类设计
//
////////////////////////////////////////////////////

#ifndef POINT_H
#define POINT_H


class point
{
private:
    float _x;
    float _y;

public:
    point();
    point(float x, float y){_x=x; _y=y;}

    // 设置坐标值
    void setX(float x){_x = x;}
    void setY(float y){_y = y;}

    // 获取坐标值
    float x()const{return _x;}
    float y()const{return _y;}
};

#endif // POINT_H
