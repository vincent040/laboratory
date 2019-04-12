#include "progressdlg.h"
#include "worker.h"
#include <QProgressDialog>
#include <iostream>

using namespace std;

progressDlg::progressDlg(QWidget *parent)
    : QDialog(parent)
{
    // 组件定义与初始化
    fileNum = new QLabel("写入行数");

    fileNumLineEdit = new QLineEdit;
    fileNumLineEdit->setText("60000");

    progressType = new QLabel("进度条类型");

    cmbox = new QComboBox;
    cmbox->addItem("进度条");
    cmbox->addItem("进度对话框");

    prgBar = new QProgressBar;
    startBtn  = new QPushButton("开始");

    // 布局
    mainLayout= new QGridLayout(this);
    mainLayout->addWidget(fileNum, 0, 0);
    mainLayout->addWidget(fileNumLineEdit, 0, 1);
    mainLayout->addWidget(progressType, 1, 0);
    mainLayout->addWidget(cmbox, 1, 1);
    mainLayout->addWidget(prgBar, 2, 0, 1, 2); // 占1行2列
    mainLayout->addWidget(startBtn, 3, 0, 1, 2);

    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);


    worker1 = new worker(this);
    totalJobs = 10000;

    // 信号与槽：点击按钮之后，显示进度条
    connect(startBtn, SIGNAL(clicked(bool)),
            this, SLOT(startProgress()));

    connect(worker1, &worker::finished,
            worker1, &QObject::deleteLater);
}

progressDlg::~progressDlg()
{

}

void progressDlg::startProgress()
{
    cout << "id: [" << QThread::currentThreadId() << "]" << endl;

    worker1->start();

    bool ok;
    int num = fileNumLineEdit->text().toInt(&ok);

    if(!ok)
        return;

    // 采用进度条方式
    if(cmbox->currentIndex() == 0)
    {
        prgBar->setRange(0, num);
        for(int i=0; i<=num; ++i)
        {
            prgBar->setValue(i);
        }
    }

    // 采用进度条对话框方式
    if(cmbox->currentIndex() == 1)
    {
        prgDlg = new QProgressDialog(this);

        prgDlg->setWindowModality(Qt::WindowModal); // 进度条行进期间不响应输入信号
        prgDlg->setMinimumDuration(5);
        prgDlg->setLabelText("正在拷贝... ...");
        prgDlg->setRange(0, num);

        connect(worker1, SIGNAL(progress(int)),
                this, SLOT(progress2(int)));

        worker1->start();
        worker1->wait();

        if(prgDlg->wasCanceled())
            return;

        delete prgDlg;
    }
}

void progressDlg::progress1(int percent)
{
    prgBar->setValue(percent);
}

void progressDlg::progress2(int percent)
{
    prgDlg->setValue(percent);
}
