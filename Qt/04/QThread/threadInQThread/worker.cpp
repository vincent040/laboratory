#include "worker.h"
#include <QDebug>
#include <QString>
#include <QThread>
#include <QDebug>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream> // for msleep

#include <QMutexLocker>

using namespace std;

worker::worker(QObject *parent)
    : QObject(parent), totalJobs(50)
{
}

void worker::function1()
{
    QString str = __FUNCTION__;
    str += ("ID:[" + QString::number(quintptr(QThread::currentThreadId())) + "]");

    emit messages(str);
}

void worker::function2()
{
    QString str = __FUNCTION__;
    str += ("ID:[" + QString::number(quintptr(QThread::currentThreadId())) + "]");

    emit messages(str);
}

void worker::setJobs(int j)
{
    totalJobs = j;
}

void worker::cancelWork()
{
    qDebug() << __FUNCTION__;
}

void worker::dowork()
{
    QString str = __FUNCTION__;
    str += ("ID:[" + QString::number(quintptr(QThread::currentThreadId())) + "]");

    for(int i=0; i<=totalJobs; ++i)
    {
        usleep(100*1000);

        if(i%2 == 1)
            emit messages(str);

        emit progress(double(i)/totalJobs * 100);

        if(QThread::currentThread()->isInterruptionRequested())
        {
            cout << "xx" << endl;
            return;
        }
    }
}
