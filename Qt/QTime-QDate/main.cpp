#include <QTime>
#include <QDate>
#include <QDebug>

using namespace std;

int main()
{
    QTime t(13,34,45);
    if(!t.isValid())
    {
        qDebug() << "时间格式非法";
        exit(0);
    }
    QDate d(2019, 04, 14);
    if(!d.isValid())
    {
        qDebug() << "日期格式非法";
        exit(0);
    }

    qDebug() << qPrintable(QString("%2, %1").arg(t.toString()).arg(d.toString()));

    QString date_time;
    date_time += QDate::currentDate().toString();
    date_time += ", ";
    date_time += QTime::currentTime().toString();
    qDebug() << qPrintable(date_time);

    return 0;
}
