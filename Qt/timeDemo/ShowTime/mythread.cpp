#include "mythread.h"
#include "QTime"

MyThread::MyThread()
{

}


void MyThread::run()
{
    while(1)
    {
        //update Time
        QString time = QTime::currentTime().toString();
        this->label->setText(time);
        sleep(1);
    }
}

void MyThread::setLabel(QLabel *lb)
{
    this->label = lb;
}
