#ifndef CHATCLIENTSOCKET_H
#define CHATCLIENTSOCKET_H
#include <QtNetwork/QTcpSocket>

class ChatClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    ChatClientSocket(QObject *parent = 0);
public slots:
    void off_line();
    void read_client_data();
signals:
    void clientOffLine(ChatClientSocket *);
    void clientData(ChatClientSocket *);
};

#endif // CHATCLIENTSOCKET_H
