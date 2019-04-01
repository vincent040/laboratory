#include "getweather.h"
#include "ui_getweather.h"

getWeather::getWeather(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::getWeather)
{
    ui->setupUi(this);
}

getWeather::~getWeather()
{
    delete ui;
}
