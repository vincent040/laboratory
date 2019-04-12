#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QString>
#include <QMutex>

class worker : public QThread
{
    Q_OBJECT

public:
    worker(QObject *parent = 0);
    ~worker();

    void function1();
    void setJobs(int num);

    // 从QThread继承的纯虚函数
    // 将需要在单独线程执行的代码写入该函数
    // 整个所有接口中，只有run函数的代码在单独线程中执行
    void run(); // function2();

    void exitThreadProperly();

// 使用两个信号，来向外界汇报线程的执行状态
signals:
    void message(const QString &str);
    void progress(double percent);


private:
    int totalJobs;

    bool runnable;
    QMutex lock;
};

#endif // WORKER_H
