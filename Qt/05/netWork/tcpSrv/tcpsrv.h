#ifndef TCPSRV_H
#define TCPSRV_H

#include <QDialog>
#include <QString>
#include "server.h"

namespace Ui {
class tcpSrv;
}

class tcpSrv : public QDialog
{
    Q_OBJECT

public:
    explicit tcpSrv(QWidget *parent = 0);
    ~tcpSrv();

public slots:
    void updateServer(QString, int);

private slots:
    void on_pushButton_clicked();

private:
    Ui::tcpSrv *ui;

    int port;
    server *srv;

};

#endif // TCPSRV_H
