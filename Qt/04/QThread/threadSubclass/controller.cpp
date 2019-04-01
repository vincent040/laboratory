#include "controller.h"
#include "ui_controller.h"
#include <QDebug>

controller::controller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::controller)
{
    ui->setupUi(this);

    ui->progressBar1->setRange(0, 100);
    ui->progressBar1->setValue(0);

    ui->progressBar2->setRange(0, 100);
    ui->progressBar2->setValue(0);

    worker1 = new worker;
    worker2 = new worker;



    connect(worker1, SIGNAL(message(QString)),
            this, SLOT(recvMsg(QString)));

    connect(worker1, SIGNAL(progress(double)),
            this, SLOT(progress1(double)));

    connect(worker2, SIGNAL(message(QString)),
            this, SLOT(recvMsg(QString)));

    connect(worker2, SIGNAL(progress(double)),
            this, SLOT(progress2(double)));

    // 回收线程资源
//    connect(worker1, &worker::finished,
//            worker1, &QObject::deleteLater);

//    connect(worker2, &worker::finished,
//            worker2, &QObject::deleteLater);
}

controller::~controller()
{
    delete ui;
}

void controller::recvMsg(const QString &msg)
{
    ui->plainTextEdit->appendPlainText(msg);
}

void controller::progress1(double percent)
{
    ui->progressBar1->setValue(percent);
}

void controller::progress2(double percent)
{
    ui->progressBar2->setValue(percent);
}

/*********** 线程1控制 **************/
void controller::on_btnStart1_clicked() // 使用start()启动单独线程
{
    if(worker1->isRunning())
        return;

    qDebug() << __FUNCTION__;

    ui->progressBar1->setValue(0);
    worker1->start(); // 内部自动创建线程，并调用run执行线程例程
}

void controller::on_btnTerm1_clicked() // 终止
{
    worker1->terminate(); // 异常终止

    if(worker1->isRunning())
        qDebug() << __FUNCTION__ << "worker1 is running.";
    if(worker1->isFinished())
        qDebug() << __FUNCTION__ << "worker1 is finished.";
}

void controller::on_btnF1_clicked() // 直接调用线程对象公共接口（未处于单独线程）
{
    worker1->function1();
}

void controller::on_btnF2_clicked() // 直接调用线程对象公共接口（未处于单独线程）
{
    worker1->run();
}


/*********** 线程2控制 **************/

void controller::on_btnStart2_clicked()
{
    if(worker2->isRunning())
        return;

    qDebug() << __FUNCTION__;

    ui->progressBar2->setValue(0);
    worker2->start(); // 启动单独的线程，去执行worker2.run()
}

void controller::on_btnTerm2_clicked()
{
    worker2->exitThreadProperly(); // 正常终止

    if(worker2->isRunning())
        qDebug() << __FUNCTION__ << "worker2 is running.";
    if(worker2->isFinished())
        qDebug() << __FUNCTION__ << "worker2 is finished.";
}

void controller::on_btnF3_clicked()
{
    worker2->function1();
}

void controller::on_btnF4_clicked()
{
    worker2->run();
}
