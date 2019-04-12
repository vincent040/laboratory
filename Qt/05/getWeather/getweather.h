#ifndef GETWEATHER_H
#define GETWEATHER_H

#include <QMainWindow>
#include <QNetworkAccessManager>

namespace Ui {
class getWeather;
}

class getWeather : public QMainWindow
{
    Q_OBJECT

public:
    explicit getWeather(QWidget *parent = 0);
    ~getWeather();

private:
    Ui::getWeather *ui;

    QNetworkAccessManager *netWorkManager;
};

#endif // GETWEATHER_H
