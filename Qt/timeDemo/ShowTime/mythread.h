#ifndef MYTHREAD_H
#define MYTHREAD_H
#include "QLabel"
#include <QThread>

class MyThread : public QThread
{
public:
    MyThread();
    void run();
    void setLabel(QLabel *lb);
private:
    QLabel *label;
};

#endif // MYTHREAD_H
