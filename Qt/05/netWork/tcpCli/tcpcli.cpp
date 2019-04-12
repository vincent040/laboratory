#include "tcpcli.h"
#include "ui_tcpcli.h"
#include <QMessageBox>
#include <QHostInfo>
#include <QDebug>



tcpCli::tcpCli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tcpCli)
{
    ui->setupUi(this);

    status = false;
    port = 50001;

    ui->lineEditPort->setText(QString::number(port));
    ui->lineEditServerIP->setText("127.0.0.1");
    ui->lineEditUsername->setText("Jack");

    serverIP = new QHostAddress();

    ui->pushButtonSend->setEnabled(false);
}

tcpCli::~tcpCli()
{
    delete ui;
}

void tcpCli::slotConnected()
{
    ui->pushButtonSend->setEnabled(true);
    ui->pushButtonEnter->setText("离开");

    QString msg = userName + ": 进入了群";
    tcpSocket->write(msg.toUtf8(), msg.length());
}

void tcpCli::slotDidconnected()
{
    ui->pushButtonSend->setEnabled(false);
    ui->pushButtonEnter->setText("进入群");
}

void tcpCli::dataReceived()
{
    while(tcpSocket->bytesAvailable() > 0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());

        tcpSocket->read(datagram.data(), datagram.size());

        QString msg = datagram.data();
        ui->listWidget->addItem(msg.left(datagram.size()));
    }
}

void tcpCli::on_pushButtonEnter_clicked()
{
    if(!status)
    {
        QString ip = ui->lineEditServerIP->text();
        if(!serverIP->setAddress(ip))
        {
            QMessageBox::information(this, "error", "服务器地址设置错误");
            return;
        }

        userName = ui->lineEditUsername->text();

        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket, SIGNAL(connected()),
                this, SLOT(slotConnected()));
        connect(tcpSocket, SIGNAL(disconnected()),
                this, SLOT(slotDidconnected()));
        connect(tcpSocket, SIGNAL(readyRead()),
                this, SLOT(dataReceived()));

        qDebug() << "尝试连接" << serverIP->toString();
        tcpSocket->connectToHost(*serverIP, port);
        if(tcpSocket->error() != 0)
        {
            qDebug() << tcpSocket->errorString();
            return;
        }
        status = true;
    }
    else
    {
        QString msg = userName + ": 离开了群";
        tcpSocket->write(msg.toUtf8(), msg.length());

        tcpSocket->disconnectFromHost();
        status = false;
    }
}

void tcpCli::on_pushButtonSend_clicked()
{
    if(ui->pushButtonSend->text() == "")
        return;

    QString msg = userName + ": " + ui->lineEdit->text();
    qint64 len = tcpSocket->write(msg.toUtf8(), msg.length());

    qDebug() << len;

    ui->lineEdit->clear();
}
