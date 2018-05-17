#ifndef HTTPINFO_H
#define HTTPINFO_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class HttpInfo;
}

class HttpInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit HttpInfo(QWidget *parent = 0);
    ~HttpInfo();

private slots:
    void on_getTimeBt_clicked();
    void on_getWeatherBt_clicked();
    void on_getAddressBt_clicked();

    //获取时间槽函数
    void get_time(QNetworkReply* reply);
    void get_weather(QNetworkReply* reply);
    void get_address(QNetworkReply* reply);

    void readReply();

private:
    Ui::HttpInfo *ui;
    QNetworkAccessManager *managerTime;
    QNetworkAccessManager *managerWeather;
    QNetworkAccessManager *managerAddress;
};

#endif // HTTPINFO_H
