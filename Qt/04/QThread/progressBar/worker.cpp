#include "worker.h"

#include <iostream>
#include <QThread>

using std::cerr;
using std::endl;

worker::worker(QObject *parent)
    :QThread(parent)
{

}

worker::~worker()
{
    cerr << __FUNCTION__ << endl;
}

void worker::run()
{
    cerr << "new thread is running, ID:";
    cerr << QThread::currentThreadId() << endl;

    for(int i=0; i<100; i++)
    {
        QThread::msleep(50);
        emit progress(i);
    }
}

