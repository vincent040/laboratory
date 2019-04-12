#include "swimmingpool.h"

swimmingPool::swimmingPool(float r)
{
    radius = r;
}

bool swimmingPool::setRadius(float r)
{
    // 设置的泳池半径至少为5米
    if(r < 5)
    {
        radius = 5;
        return false;
    }

    radius = r;
    return true;
}

float swimmingPool::getRadius()
{
    return radius;
}

swimmingPool::swimmingPool()
{
    // 默认泳池半径为5米
    radius = 5;
}

float swimmingPool::costOfFencing()
{
    float outerCircle = 2 * PI * (radius + 3);
    float innerCircle = 2 * PI * radius;

    return (outerCircle + innerCircle) * unitCostOfFencing;
}

float swimmingPool::costOfPassage()
{
    float outerCircle = PI * (radius + 3) * (radius + 3);
    float innerCircle = PI * radius * radius;

    return (outerCircle - innerCircle) * unitCostOfPassage;
}

float swimmingPool::totalCost()
{
    return costOfFencing() + costOfPassage();
}

