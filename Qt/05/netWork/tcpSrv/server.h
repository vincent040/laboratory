#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include <QDebug>
#include <QList>
#include "clientsock.h"

class server : public QTcpServer
{
    Q_OBJECT

public:
    server(QObject *parent=0, int port=0);

    QList<clientSock *> userList;

signals:
    void updateServer(QString, int);

public slots:
    void updateClients(QString, int);
    void slotDisconnectted(int);

protected:
    void incomingConnection(int sockfd);
};

#endif // SERVER_H
