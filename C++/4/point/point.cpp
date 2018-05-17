#include "point.h"

point::point(float x, float y)
{
    this->x = x;
    this->y = y;
}

void point::setX(float x)
{
    this->x = x;
}

void point::setY(float y)
{
    this->y = y;
}

float point::getX()
{
    return x;
}

float point::getY()
{
    return y;
}
