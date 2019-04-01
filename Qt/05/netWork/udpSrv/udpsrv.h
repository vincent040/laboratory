#ifndef UDPSRV_H
#define UDPSRV_H

#include <QWidget>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QUdpSocket>
#include <QTimer>

namespace Ui {
class udpSrv;
}

class udpSrv : public QWidget
{
    Q_OBJECT

public:
    explicit udpSrv(QWidget *parent = 0);
    ~udpSrv();

public slots:
    void on_pushButton_clicked();
    void timeout();

private:
    Ui::udpSrv *ui;

    int port;
    bool isStarted;

    QUdpSocket *udpSocket;
    QTimer *timer;
};

#endif // UDPSRV_H
