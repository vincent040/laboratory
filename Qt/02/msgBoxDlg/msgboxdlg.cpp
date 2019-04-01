#include "msgboxdlg.h"
#include <QMessageBox> // question/information/critical/about

msgBoxDlg::msgBoxDlg(QWidget *parent) :
    QDialog(parent)
{
    // 组件
    label = new QLabel("请选择一种消息框");
    questionBtn = new QPushButton("question消息匡");

    // 布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    mainLayout->addWidget(questionBtn);

    // 信号与槽
    connect(questionBtn, SIGNAL(clicked(bool)),
            this, SLOT(showQuestionMsg()));
}

msgBoxDlg::~msgBoxDlg()
{
}

void msgBoxDlg::showQuestionMsg()
{
    label->setText("问题消息框");

    switch(QMessageBox::question(this,
                                 "question消息框",
                                 "是否结束程序？",
                                 QMessageBox::Ok | QMessageBox::Cancel, // 供选择的按钮
                                 QMessageBox::Ok)) // 默认按钮
    {
    case QMessageBox::Ok:
        label->setText("OK");
        break;

    case QMessageBox::Cancel:
        label->setText("CANCEL");
        break;
    }
}
