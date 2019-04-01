#ifndef CLIENTSOCK_H
#define CLIENTSOCK_H

#include <QTcpSocket>
#include <QObject>

class clientSock : public QTcpSocket
{
    Q_OBJECT

public:
    clientSock(QObject *parent=0);

signals:
    void updateClients(QString, int);
    void disconnected(int);

protected slots:
    void dataReceived();
    void slotDisconnected();
};

#endif // CLIENTSOCK_H
