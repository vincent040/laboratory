#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QObject>

class example : public QObject
{
    Q_OBJECT

public:
    example()
    {
//        this->xxxx; // 观察各种不同成员在自动匹配时的图标
    }

    int publicFunc();
    int publicVar;

    int static publicStaticVar;
    int static const publicStaticConstVar;

    enum enumData{zero, one, two};
protected:
    int protectedFunc();
    int protectedVar;

private:
    int privateFunc();
    int privateVar;


signals:
    void signal();


public slots:
    int publicSlot();

protected slots:
    int protectedSlot();

private slots:
    int privateSlot();

};

#endif // EXAMPLE_H
