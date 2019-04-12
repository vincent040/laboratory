#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <worker.h>

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

    void recvMsg(const QString &msg);
    void progress1(double percent);
    void progress2(double percent);

    void on_btnStart1_clicked();
    void on_btnTerm1_clicked();
    void on_btnF1_clicked();
    void on_btnF2_clicked();

    void on_btnStart2_clicked();
    void on_btnTerm2_clicked();
    void on_btnF3_clicked();
    void on_btnF4_clicked();

private:
    Ui::controller *ui;

    // 包含两个线程对象
    worker *worker1, *worker2;
};

#endif // CONTROLLER_H
