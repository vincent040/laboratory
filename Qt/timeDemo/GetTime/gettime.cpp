#include "gettime.h"
#include "ui_gettime.h"
#include <QDebug>

GetTime::GetTime(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GetTime)
{
    ui->setupUi(this);
    //创建网络管理器
    manager = new QNetworkAccessManager();

    //当请求数据有返回时候会发送信号
    connect(manager , SIGNAL(finished(QNetworkReply*)),this, SLOT(readmsg()));
}

GetTime::~GetTime()
{
    delete ui;
}

void GetTime::on_pushButton_clicked()
{
    QNetworkRequest request(QUrl("http://gb.weather.gov.hk/cgi-bin/hko/localtime.pl"));
    reply = manager->get(request);
}

void GetTime::readmsg()
{
    qDebug()<<reply->readAll();
}


