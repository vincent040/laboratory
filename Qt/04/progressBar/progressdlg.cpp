#include "progressdlg.h"
#include <QProgressDialog>
#include <iostream>

using namespace std;

progressDlg::progressDlg(QWidget *parent)
    : QDialog(parent)
{
    // 组件定义与初始化
    fileNum = new QLabel("文件数量");

    fileNumLineEdit = new QLineEdit;
    fileNumLineEdit->setText("10000");

    progressType = new QLabel("显示类型");

    cmbox = new QComboBox ;
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
    mainLayout->addWidget(startBtn, 3, 1);

    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);


    // 信号与槽
    connect(startBtn, SIGNAL(clicked(bool)),
            this, SLOT(startProgress()));
}

progressDlg::~progressDlg()
{

}

void progressDlg::startProgress()
{
    bool ok;
    int num = fileNumLineEdit->text().toInt(&ok);

    if(!ok)
        return;

    cout << cmbox->currentIndex() << endl;

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
        QProgressDialog *prgDlg = new QProgressDialog(this);

        prgDlg->setWindowModality(Qt::WindowModal); // 进度条行进期间不响应输入信号
        prgDlg->setMinimumDuration(5);
        prgDlg->setLabelText("正在拷贝... ...");
//        prgDlg->setValue(0);
        prgDlg->setRange(0, num);

        for(int i=0; i<=num; ++i)
        {
            prgDlg->setValue(i);

            if(prgDlg->wasCanceled())
                return;
        }

        delete prgDlg;
//        prgDlg->setLabelText("拷贝成功！");
    }
}
