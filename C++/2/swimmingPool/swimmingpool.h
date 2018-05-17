#ifndef SWIMMINGPOOL_H
#define SWIMMINGPOOL_H


class swimmingPool
{
public:
    swimmingPool();
    swimmingPool(float r);

    bool setRadius(float r);
    float getRadius();

    float costOfFencing();
    float costOfPassage();
    float totalCost();

private:
    float radius;

    const int unitCostOfFencing = 35;
    const int unitCostOfPassage = 20;

    const float PI = 3.141592654;
};

#endif // SWIMMINGPOOL_H
