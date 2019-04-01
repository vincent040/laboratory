#include "mouseevent.h"
#include "ui_mouseevent.h"

#include <QString>

mouseEvent::mouseEvent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mouseEvent)
{
    ui->setupUi(this);

    status = new QLabel("当前位置：");
    status->setFixedWidth(100);

    position = new QLabel("");
    position->setFixedWidth(100);

    // 状态栏statusBar是主窗体QMainWindow的静态函数
    QMainWindow::statusBar()->addPermanentWidget(status);
                 statusBar()->addPermanentWidget(position);

    // 调整当前窗体的尺寸
    resize(400, 200);
}

mouseEvent::~mouseEvent()
{
    delete ui;
}

void mouseEvent::mousePressEvent(QMouseEvent *e)
{
    QString str = "(" + QString::number(e->x()) + ", " +
                        QString::number(e->y()) + ")";

    if(e->button() == Qt::LeftButton)
    {
        statusBar()->showMessage("左键：" + str);
    }

    else if(e->button() == Qt::RightButton)
    {
        statusBar()->showMessage("右键：" + str);
    }

    else if(e->button() == Qt::MidButton)
    {
        statusBar()->showMessage("中键：" + str);
    }
}

void mouseEvent::mouseMoveEvent(QMouseEvent *e)
{
    position->setText("(" + QString::number(e->x()) +
                      ", "+ QString::number(e->y()) + ")");
}

void mouseEvent::mouseReleaseEvent(QMouseEvent *e)
{
    QString str = "(" + QString::number(e->x()) +
                  "," + QString::number(e->y()) + ")";

    // 更变状态栏信息，维持3秒钟
    statusBar()->showMessage("释放在：" + str, 3*1000);
}

void mouseEvent::mouseDoubleClickEvent(QMouseEvent *e)
{
    position->setText("无可奉告");
}
