#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>

class worker : public QObject
{
    Q_OBJECT
public:
    explicit worker(QObject *parent = 0);

    void setJobs(int j);

// 定义两个信号，向外界汇报worker的工作进展
signals:
    void messages(const QString &str);
    void progress(double percent);

// 通过信号，接收外界指派的任务
// 所有的任务，都将在一个独立的线程中被执行
public slots:
    void dowork();
    void function1();
    void function2();

    void cancelWork();

private:
    int totalJobs;
};

#endif // WORKER_H
