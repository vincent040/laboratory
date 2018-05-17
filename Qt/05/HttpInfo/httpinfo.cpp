#include "httpinfo.h"
#include "ui_httpinfo.h"
#include <QTextCodec>
#include <QDebug>

HttpInfo::HttpInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HttpInfo)
{
    ui->setupUi(this);
    //this->showFullScreen();
    managerAddress = NULL;
    managerTime = NULL;
    managerWeather = NULL;
}

HttpInfo::~HttpInfo()
{
    delete ui;
    delete managerTime;
    delete managerAddress;
    delete managerWeather;
}

//获取当前北京时间
void HttpInfo::on_getTimeBt_clicked()
{
    if(managerTime == NULL)
    {
        managerTime = new QNetworkAccessManager();
        connect(managerTime, SIGNAL(finished(QNetworkReply*)), this, SLOT(get_time(QNetworkReply*)));
    }

    //url地址
    QUrl url("http://gb.weather.gov.hk/cgi-bin/hko/localtime.pl");
    //创建请求
    QNetworkRequest request(url);
    //通过管理器获取数据
    managerTime->get(request);



    //T弹出窗口
    QWidget *win = new QWidget();
    win->setGeometry(100,  300, 200,200);
    QLabel *lab = new QLabel(win);
    lab->setText("55555555555555555555");
    lab->resize(200, 200);
    win->show();

}

//获取当前天气
void HttpInfo::on_getWeatherBt_clicked()
{
    if(managerWeather == NULL)
    {
        managerWeather = new QNetworkAccessManager();
        connect(managerWeather, SIGNAL(finished(QNetworkReply*)), this, SLOT(get_weather(QNetworkReply*)));
    }

    //url地址
    QUrl url("http://www.weather.com.cn/data/cityinfo/101010100.html");
    //创建请求
    QNetworkRequest request(url);
    //通过管理器获取数据
    managerWeather->get(request);

}

//获取当前城市位置
void HttpInfo::on_getAddressBt_clicked()
{
    if(managerAddress == NULL)
    {
        managerAddress = new QNetworkAccessManager();
        connect(managerAddress, SIGNAL(finished(QNetworkReply*)), this, SLOT(get_address(QNetworkReply*)));
    }
    //url地址
    QUrl url("http://w.1616.net/chaxun/iptolocal.php");
    //创建请求
    QNetworkRequest request(url);
    //通过管理器获取数据
    managerAddress->get(request);

}

void HttpInfo::get_time(QNetworkReply* reply)
{
    QString msg = reply->readAll();
    QStringList list = msg.split("\n");
    //qDebug()<<list;
    ui->dataLebel->setText(list.at(0)+"-"+list.at(1)+"-"+list.at(2));
    ui->timeLabel->setText(list.at(3)+":"+list.at(4)+":"+list.at(5));
}
void HttpInfo::get_weather(QNetworkReply* reply)
{
    QString msg = reply->readAll();
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(msg.toUtf8(), &error);//创建一个JSonDocument对象
    if(error.error == QJsonParseError::NoError)
    {
        //没有错误说明是json数据
        QJsonObject obj =  document.object();
        QJsonValue val = obj.value("weatherinfo");
        obj = val.toObject();
        ui->textEdit->append(obj.value("temp1").toString());
       ui->textEdit->append(obj.value("temp2").toString());
        ui->textEdit->append(obj.value("weather").toString());
    }

}
void HttpInfo::get_address(QNetworkReply* reply)
{
    QString msg = reply->readAll();
    int pos = msg.indexOf("]");
    msg.remove(pos, msg.length()-pos);

    pos = msg.indexOf("[");
    msg.remove(0, pos+1);

    QStringList list = msg.split(",");

    msg = list.at(1);
    ui->addressLabel->setText(msg.remove('\''));
}
