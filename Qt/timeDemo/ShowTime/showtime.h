#ifndef SHOWTIME_H
#define SHOWTIME_H

#include <QMainWindow>
#include "mythread.h"

namespace Ui {
class ShowTime;
}

class ShowTime : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowTime(QWidget *parent = 0);
    ~ShowTime();

private:
    Ui::ShowTime *ui;
    MyThread *thrd;
};

#endif // SHOWTIME_H
