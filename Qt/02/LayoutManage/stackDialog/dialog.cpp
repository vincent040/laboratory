#include "dialog.h"
#include <QHBoxLayout> // 水平布局

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    // 初始化列表视图控件
    list = new QListWidget(this);
    list->insertItem(0, "窗口1");
    list->insertItem(1, "窗口2");
    list->insertItem(2, "窗口3");

    // 初始化标签
    label1 = new QLabel("内容1");
    label2 = new QLabel("内容2");
    label3 = new QLabel("内容3");

    // 初始化堆叠窗体，并设置其父对象为本对话框
    stack = new QStackedWidget(this);

    // 将三个标签依次插入到堆叠窗体中
    // 对应stack的0、1、2……等下标（index）
    stack->addWidget(label1);
    stack->addWidget(label2);
    stack->addWidget(label3);

    QHBoxLayout *mainlayout = new QHBoxLayout(this);

    // 1，将列表视图放到水平布局中（从最左边开始)
    mainlayout->addWidget(list);

    // 2，将堆叠窗体继续放到水平布局中，阻止拉伸，设置水平居中
    mainlayout->addWidget(stack, 0, Qt::AlignHCenter);

    // 3，设置水平布局中，各个水平部件的宽度比例（1:3)
    mainlayout->setStretchFactor(list, 1);
    mainlayout->setStretchFactor(stack, 3);

    // 4，将列表视图状态的变化，发射信号给堆叠窗体更换显示内容
    connect(list, SIGNAL(currentRowChanged(int)),
            stack,SLOT(setCurrentIndex(int)));
}

Dialog::~Dialog()
{
}
