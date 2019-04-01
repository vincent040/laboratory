#ifndef POINT_H
#define POINT_H


class point
{
public:
    point(float x=0.0, float y=0.0);

    void setX(float x);
    void setY(float y);

    float getX();
    float getY();

private:
    float x;
    float y;
};

#endif // POINT_H
