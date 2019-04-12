#include "example.h"
#include <QDebug>
#include <iostream>

using std::cout;

int example::publicFunc()
{
    return 0;
}

int example::protectedFunc()
{
    return 0;
}

int example::privateFunc()
{
    return 0;
}

int example::publicSlot()
{
    qDebug() << __FUNCTION__;
    return 0;
}

int example::protectedSlot()
{
    qDebug() << __FUNCTION__;
    return 0;
}

int example::privateSlot()
{
    qDebug() << __FUNCTION__;
    return 0;
}
