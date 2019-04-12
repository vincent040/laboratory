#include "controller.h"
#include "ui_controller.h"
#include "worker.h"
#include <QThread>
#include <QDebug>
#include <iostream>

using namespace std;

controller::controller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::controller)
{
    ui->setupUi(this);

    // 组件初始化
    ui->progressBar1->setRange(0, 100);
    ui->progressBar1->setValue(0);
    ui->progressBar2->setRange(0, 100);
    ui->progressBar2->setValue(0);

    // 创建两个线程对象
    workthread1 = new QThread;
    workthread2 = new QThread;

    worker1 = new worker;
    worker2 = new worker;

    // 将worker放进线程对象中，worker中所有的slot代码
    // 都将运行在单独的线程中，worker中的slot函数可以被
    // 任意其他对象、其他线程的信号所连接
    worker1->moveToThread(workthread1);
    worker2->moveToThread(workthread2);

    // 将按钮连接到worker的槽函数上
    connect(ui->btnTerm1, &QPushButton::clicked,
            workthread1, &QThread::requestInterruption);
    connect(ui->btnF1, SIGNAL(clicked(bool)),
            worker1, SLOT(function1()));
    connect(ui->btnF2, SIGNAL(clicked(bool)),
            worker1, SLOT(function2()));

    connect(ui->btnStart2, SIGNAL(clicked(bool)),
            worker2, SLOT(dowork()));
    connect(ui->btnTerm2, SIGNAL(clicked(bool)),
            worker2, SLOT(cancelWork()));
    connect(ui->btnF3, SIGNAL(clicked(bool)),
            worker2, SLOT(function1()));
    connect(ui->btnF4, SIGNAL(clicked(bool)),
            worker2, SLOT(function2()));



    // 连接从worker发来的信号（接收worker汇报）
    connect(worker1, SIGNAL(messages(QString)),
            this, SLOT(recvMsg(QString)));
    connect(worker1, SIGNAL(progress(double)),
            this, SLOT(progress1(double)));

    connect(worker2, SIGNAL(messages(QString)),
            this, SLOT(recvMsg(QString)));
    connect(worker2, SIGNAL(progress(double)),
            this, SLOT(progress2(double)));


    // 连接从线程对象发来的信号（监控线程状态）
    connect(workthread1, SIGNAL(started()),
            this, SLOT(watching()));
    connect(workthread2, SIGNAL(started()),
            this, SLOT(watching()));

    connect(workthread1, SIGNAL(finished()),
            this, SLOT(watching()));
    connect(workthread2, SIGNAL(finished()),
            this, SLOT(watching()));

    workthread2->start();
}

controller::~controller()
{
    delete ui;
}

void controller::recvMsg(const QString &str)
{
    ui->plainTextEdit->appendPlainText(str);
}

void controller::progress1(double percent)
{
    ui->progressBar1->setValue(percent);
}

void controller::progress2(double percent)
{
    ui->progressBar2->setValue(percent);
}

/************** 监控线程状态 **************/
void controller::watching()
{
    if(workthread1->isRunning())
        cout << "thread1 is startted" << endl;
    if(workthread2->isRunning())
        cout << "thread2 is startted" << endl;

    if(workthread1->isFinished())
        cout << "thread1 is finished" << endl;
    if(workthread2->isFinished())
        cout << "thread2 is finished" << endl;
}

void controller::on_btnStart1_clicked()
{
    if(workthread1->isRunning())
        return;

    workthread1->start();
    worker1->dowork();
}
