#include "chatserver.h"
#include "ui_chatserver.h"
#include <QDebug>
#include <QMessageBox>

ChatServer::ChatServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatServer)
{
    ui->setupUi(this);
    mServer = new QTcpServer();
    connect(mServer,SIGNAL(newConnection()),this, SLOT(new_client_connect()));
    mServer->listen(QHostAddress::Any, 9898);
    //屏蔽发送按钮
    ui->sendBt->setEnabled(false);
}

ChatServer::~ChatServer()
{
    delete ui;
}

void ChatServer::on_sendBt_clicked()
{
    QString msg = ui->sendEidt->toPlainText();
    //提示如果没有输入就提示
    if(msg.isEmpty())
    {
        QMessageBox::warning(this, "温馨提示", "请输入内容");
        return ;
    }

    int row = ui->onLineList->currentRow();
    if(row < 0)
    {
        QMessageBox::warning(this, "温馨提示", "请选择要发送的用户");
        return ;
    }

    //从用户socket列表取出对应的socket发送数据
    clientSocket.at(row)->write(msg.toLatin1().data());
    ui->sendEidt->clear();

}

void ChatServer::on_clearBt_clicked()
{

}

void ChatServer::new_client_connect()
{
    qDebug()<<"new connect";
    //自定义Tcpsocket
    ChatClientSocket *mSocket = new ChatClientSocket();
    bool ret = mSocket->setSocketDescriptor(mServer->nextPendingConnection()->socketDescriptor());
    if(ret)
    {
        qDebug()<<"suc";
    }
    connect(mSocket,SIGNAL(clientData(ChatClientSocket*)), this ,SLOT(read_client_data(ChatClientSocket*)));
    connect(mSocket, SIGNAL(clientOffLine(ChatClientSocket*)), this, SLOT(client_off_line(ChatClientSocket*)));

    //把上线的客户端添加到onLineList中
    QString ip = mSocket->peerAddress().toString();
    ip.remove("::ffff:");
    ui->onLineList->addItem(ip);

    clientSocket.append(mSocket);
    //在toolbox栏显示用户数
    ui->toolBox->setItemText(0, "在线用户:"+QString::number(ui->onLineList->count()));

    //如果当前上线用户在离线中存在把离线列表中的用户删除
    for(int i=0; i<ui->offLineList->count(); i++)
    {
       if(ui->offLineList->item(i)->text() == ip)
       {
                QListWidgetItem *item = ui->offLineList->takeItem(i);
                delete item;
                break;
        }
    }

    //设置按钮生效
    ui->sendBt->setEnabled(true);
}

void ChatServer::read_client_data(ChatClientSocket*obj)
{
    qDebug()<<obj->readAll();
}



void ChatServer::client_off_line(ChatClientSocket*obj)
{
    //从在线列表中找到已经掉线的客户端
    int row = clientSocket.indexOf(obj);
    clientSocket.removeOne(obj);

    //删除界面list中的onLineList
    QListWidgetItem *item =  ui->onLineList->takeItem(row);
    ui->offLineList->addItem(item);

    //在toolbox栏显示用户数
    ui->toolBox->setItemText(1, "离线用户:"+QString::number(ui->offLineList->count()));

    //在toolbox栏显示用户数
    ui->toolBox->setItemText(0, "在线用户:"+QString::number(ui->onLineList->count()));
}
