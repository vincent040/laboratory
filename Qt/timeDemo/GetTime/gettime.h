#ifndef GETTIME_H
#define GETTIME_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

namespace Ui {
class GetTime;
}

class GetTime : public QMainWindow
{
    Q_OBJECT

public:
    explicit GetTime(QWidget *parent = 0);
    ~GetTime();

private slots:
    void on_pushButton_clicked();
    void readmsg();
private:
    Ui::GetTime *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
};

#endif // GETTIME_H
