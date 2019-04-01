#include "udpsrv.h"
#include "ui_udpsrv.h"

#include <QtNetwork/QHostAddress>
#include <QDebug>

udpSrv::udpSrv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::udpSrv)
{
    ui->setupUi(this);

    port = 50001;
    isStarted = false;

    udpSocket = new QUdpSocket(this);
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()),
            this, SLOT(timeout()));
}

udpSrv::~udpSrv()
{
    delete ui;
}

void udpSrv::on_pushButton_clicked()
{
    // 开始
    if(!isStarted)
    {
        isStarted = true;

        ui->pushButton->setText("停止");
        timer->start(1000); // 1秒
    }

    // 停止
    else
    {
        isStarted = false;

        ui->pushButton->setText("开始");
        timer->stop();
    }
}

void udpSrv::timeout()
{
    QString msg = ui->lineEdit->text();

    int length = 0;

    if(msg == "")
        return;

    length = udpSocket->writeDatagram(msg.toLocal8Bit(),
                                      msg.length(),
                                      QHostAddress::Broadcast,
                                      port);
}
