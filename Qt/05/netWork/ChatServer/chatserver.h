#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include "chatclientsocket.h"
#include <QHostAddress>
#include <QList>

namespace Ui {
class ChatServer;
}

class ChatServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatServer(QWidget *parent = 0);
    ~ChatServer();

private slots:
    void on_sendBt_clicked();
    void on_clearBt_clicked();
    void new_client_connect();
    void read_client_data(ChatClientSocket*);
    void client_off_line(ChatClientSocket*);


private:
    Ui::ChatServer *ui;
    QTcpServer *mServer;
    QList<ChatClientSocket*> clientSocket;
};

#endif // CHATSERVER_H
