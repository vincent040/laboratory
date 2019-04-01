#include "clientsock.h"

clientSock::clientSock(QObject *parent)
{
    connect(this, SIGNAL(readyRead()),
            this, SLOT(dataReceived()));

    connect(this, SIGNAL(disconnected()),
            this, SLOT(slotDisconnected()));
}

void clientSock::dataReceived()
{
    while(bytesAvailable() > 0)
    {
        int length = bytesAvailable();

        char buf[1024]; // 假设一次读到的数据不超过1024
        read(buf, length);

        // 将消息发送给所有人
        QString msg = buf;
        emit updateClients(msg, length);
    }
}

void clientSock::slotDisconnected()
{
    // 将断开连接的情况告诉所有人
    emit disconnected(this->socketDescriptor());
}
