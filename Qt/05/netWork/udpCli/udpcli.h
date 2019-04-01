#ifndef UDPCLI_H
#define UDPCLI_H

#include <QDialog>
#include <QUdpSocket>

namespace Ui {
class udpCli;
}

class udpCli : public QDialog
{
    Q_OBJECT

public:
    explicit udpCli(QWidget *parent = 0);
    ~udpCli();

public slots:
    void dataReceived();

private:
    Ui::udpCli *ui;

    int port;
    QUdpSocket *udpSocket;
};

#endif // UDPCLI_H
