#include "tcpsrv.h"
#include "ui_tcpsrv.h"

tcpSrv::tcpSrv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tcpSrv)
{
    ui->setupUi(this);

    port = 50001;
    ui->lineEdit->setText(QString::number(port));
}

tcpSrv::~tcpSrv()
{
    delete ui;
}

void tcpSrv::updateServer(QString msg, int length)
{
    ui->listWidget->addItem(msg.left(length));
}

void tcpSrv::on_pushButton_clicked()
{
    srv = new server(this, port);

    connect(srv, SIGNAL(updateServer(QString,int)),
            this, SLOT(updateServer(QString,int)));

    ui->pushButton->setEnabled(false);
}
