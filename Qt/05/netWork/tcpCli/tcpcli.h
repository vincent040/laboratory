#ifndef TCPCLI_H
#define TCPCLI_H

#include <QDialog>
#include <QtNetwork/QHostAddress>
#include <QTcpSocket>
#include <QString>
#include <QDebug>

namespace Ui {
class tcpCli;
}

class tcpCli : public QDialog
{
    Q_OBJECT

public:
    explicit tcpCli(QWidget *parent = 0);
    ~tcpCli();

public slots:
    void slotConnected();
    void slotDidconnected();
    void dataReceived();

private slots:
    void on_pushButtonEnter_clicked();

    void on_pushButtonSend_clicked();

private:
    Ui::tcpCli *ui;

    bool status;
    int port;
    QHostAddress *serverIP;
    QString userName;

    QTcpSocket *tcpSocket;
};

#endif // TCPCLI_H
