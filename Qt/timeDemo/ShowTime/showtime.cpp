#include "showtime.h"
#include "ui_showtime.h"

ShowTime::ShowTime(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowTime)
{
    ui->setupUi(this);
    thrd = new MyThread();
    thrd->setLabel(ui->label);
    thrd->start();
}

ShowTime::~ShowTime()
{
    delete ui;
}
