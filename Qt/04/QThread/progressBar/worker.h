#ifndef WORKER_H
#define WORKER_H

#include <QThread>

class worker : public QThread
{
    Q_OBJECT

public:
    worker(QObject *parent = 0);
    ~worker();

    void run() ;

signals:
    void progress(int percent);
};

#endif // WORKER_H
