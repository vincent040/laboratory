#include "chatclientsocket.h"
#include <QDebug>

ChatClientSocket::ChatClientSocket(QObject *parent):QTcpSocket(parent)
{
    connect(this, SIGNAL(disconnected()),this, SLOT(off_line()));
    connect(this, SIGNAL(readyRead()), this, SLOT(read_client_data()));
}

void ChatClientSocket::off_line()
{
    qDebug()<<"===================";
    emit clientOffLine(this);
}

void ChatClientSocket::read_client_data()
{
    emit clientData(this);
}
