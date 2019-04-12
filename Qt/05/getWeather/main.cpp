#include "getweather.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    getWeather w;
    w.show();

    return a.exec();
}
