#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <worker.h>
#include <QThread>
#include <QString>
#include "worker.h"

namespace Ui {
class controller;
}

class controller : public QWidget
{
    Q_OBJECT

public:
    explicit controller(QWidget *parent = 0);
    ~controller();

private slots:
    void recvMsg(const QString &str);
    void progress1(double percent);
    void progress2(double percent);

    void watching();

    void on_btnStart1_clicked();

private:
    Ui::controller *ui;

    // 定义两个线程对象，可以将有需要单独线程的任务放进里面
    QThread *workthread1;
    QThread *workthread2;

    worker *worker1;
    worker *worker2;
};

#endif // CONTROLLER_H
