#include "mainwindow.h"
#include <QTextEdit>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // 创建一个文本编辑框，作为窗体的主窗口
    QTextEdit *te = new QTextEdit("主窗口", this);
    te->setAlignment(Qt::AlignCenter);
    setCentralWidget(te);

    // 创建一个停靠窗体dock1
    QDockWidget *dock1 = new QDockWidget("停靠窗体1", this);
    dock1->setFeatures(QDockWidget::DockWidgetMovable); // 可移动
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea |
                          Qt::RightDockWidgetArea); // 可移动的范围

    QTextEdit *te1 = new QTextEdit("8888", this);
    te1->setAlignment(Qt::AlignCenter);

    // 将文本框te1添加到停靠窗体dock1中
    dock1->setWidget(te1);

    // 将停靠窗体dock1设置到主窗口的右边（否则默认在左边）
    addDockWidget(Qt::RightDockWidgetArea, dock1);



    // 再创建第二个停靠窗体dock2
    QDockWidget *dock2 = new QDockWidget("停靠窗体2", this);
    dock2->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dock2->setAllowedAreas(Qt::AllDockWidgetAreas);

    QTextEdit *te2 = new QTextEdit("999", this);
    te2->setAlignment(Qt::AlignCenter);

    // 将文本框te1添加到停靠窗体dock1中，并将dock2添加到主窗体
    dock2->setWidget(te2);
    addDockWidget(Qt::BottomDockWidgetArea, dock2);
}

MainWindow::~MainWindow()
{
}
