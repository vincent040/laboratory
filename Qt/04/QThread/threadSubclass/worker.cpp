#include "worker.h"
#include <QDebug>
#include <iostream>
#include <QString>

worker::worker(QObject *parent)
    :QThread(parent), totalJobs(100)
{
    runnable = false;
}

worker::~worker()
{
}

void worker::function1()
{
    QString ID = QString::number(quintptr(QThread::currentThreadId()));
    emit message(QString("[%1] ID:%2").arg(__FUNCTION__).arg(ID));
}

void worker::setJobs(int num)
{
    totalJobs = num;
}

// function2
void worker::run()
{
    runnable = true;

    QString ID = QString::number(quintptr(QThread::currentThreadId()));

    for(int i=0; i<=totalJobs; ++i)
    {
        msleep(50); // 代表做一段时间的事情

        // 每完成一个阶段的任务，通过信号向外界汇报当前进度
        emit message(QString("[%1] ID:%2").arg(__FUNCTION__).arg(ID));
        emit progress(double(i)/totalJobs * 100);

        QMutexLocker m(&lock);
        if(!runnable)
            return;
    }

    // 从这个函数退出之后，线程便终止了
}

void worker::exitThreadProperly()
{
    QMutexLocker m(&lock);
    runnable = false;
}

