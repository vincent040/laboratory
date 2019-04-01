#include "server.h"
#include <QDebug>

server::server(QObject *parent, int port)
    :QTcpServer(parent)
{
    // 监听指定的IP和PORT
    listen(QHostAddress::Any, port);

    qDebug() << "listenning on " << QHostAddress::Any << ":" << port;
}

void server::updateClients(QString msg, int length)
{
    emit updateServer(msg, length); // 更新服务端对话框状态

    for(int i=0; i<userList.count(); ++i)
    {
        QTcpSocket *item = userList.at(i);

        item->write(msg.toLatin1(), length);
    }
}

void server::slotDisconnectted(int sockfd)
{
    // 将某掉线的用户删除
    for(int i=0; i<userList.count(); ++i)
    {
        QTcpSocket *item = userList.at(i);

        if(item->socketDescriptor() == sockfd)
        {
            userList.removeAt(i);
            return;
        }
    }
}

// 处理新连接请求
void server::incomingConnection(int sockfd)
{
   qDebug() << "新连接：" << sockfd;

   clientSock *newcli = new clientSock(this);

   // 客户对象收到消息通知我
   connect(newcli, SIGNAL(updateClients(QString,int)),
           this, SLOT(updateClients(QString,int)));

   // 客户对象断开连接通知我
   connect(newcli, SIGNAL(disconnected(int)),
           this, SLOT(slotDisconnectted(int)));

   newcli->setSocketDescriptor(sockfd);
   userList.append(newcli);
}
