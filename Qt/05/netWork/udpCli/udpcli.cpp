#include "udpcli.h"
#include "ui_udpcli.h"
#include <QHostAddress>
#include <QMessageBox>

udpCli::udpCli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::udpCli)
{
    ui->setupUi(this);

    port = 50001;
    udpSocket = new QUdpSocket(this);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(dataReceived()));

    bool result = udpSocket->bind(port);
    if(!result)
    {
        QMessageBox::information(this, "error", "udp端口绑定出错");
        return;
    }
}

udpCli::~udpCli()
{
    delete ui;
}

void udpCli::dataReceived()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        QString msg = datagram.data();
        ui->plainTextEdit->insertPlainText(msg);
    }
}
