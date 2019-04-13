#include <QString>
#include <QStringList>
#include <QDebug>
#include <unistd.h>
#include <string>
#include <iostream>

using std::string;

int main(int argc, char *argv[])
{
    // 赋值和初始化
    QString s1 = "粤嵌";
    QString s2("通信");
    QString *s3 = new QString("科技");
    QString s4 = (s1 + s2 + *s3);
    s4 += "股份";
    s4.append("有限公司");

    qDebug() << s1;
    qDebug() << s2;
    qDebug() << *s3;
    qDebug() << s4;
    qDebug() << qPrintable(s1+s2+*s3);
    qDebug() << qPrintable(s4);
    qDebug() << qPrintable(QString("粤嵌通信科技股份"));

    // 组合字符串①
    QString s5;
    s5.sprintf("股票代码:%d, 市值:￥%.1f亿", 839909, 8.88);
    qDebug() << qPrintable(s5);

    // 组合字符串②
    QString s6 = QString("股票代码:%1, 市值:￥%2亿").arg(839909).arg(8.88);
    qDebug() << qPrintable(s6);

    // 长度与容量
    QString s7("啊aa");
    qDebug() << s7.length(); // 3
    qDebug() << s7.size(); // 3
    qDebug() << s7.capacity(); // 5
    qDebug() << strlen(s7.toStdString().c_str()); // 5

    // Qt、C++与C风格的转换
    QString s8("粤嵌999");
    qDebug() << strlen(s8.toStdString().c_str()); // Qt --> C++ --> C
    qDebug() << QString("粤嵌777"); // C --> Qt
    qDebug() << QString(string("粤嵌777").c_str());// C --> C++ --> Qt

    // 字符串比较
    QString s9  = "123";
    QString s10 = "aBc";
    if(s9 > s10)
        qDebug() << QString("%1 大于 %2").arg(s9).arg(s10);
    else if(s9 == s10)
        qDebug() << QString("%1 等于 %2").arg(s9).arg(s10);
    else
        qDebug() << QString("%1 小于 %2").arg(s9).arg(s10);

    // 数值转换
    QString s11 = "1008";
    QString s12 = "3.14";
    if(s11.toInt() > s12.toFloat())
        qDebug() << QString("%1 大于 %2").arg(s11).arg(s12);
    else
        qDebug() << QString("%1 小于 %2").arg(s11).arg(s12);

    QString s13 = "0x123";
    bool ok;
    int a = s13.toInt(&ok, 16);
    if(ok)
        qDebug("a: %#x", a);
    else
        qDebug() << "转换失败";

    // 字符串列表
    QStringList gec;
    gec.push_back(s4);
    gec.push_back(s5);

    qDebug() << gec[0].toStdString().c_str() << ":"
             << gec[1].toStdString().c_str();

    QString s14;
    QStringList::ConstIterator it = gec.begin();
    s14 += *(it++);
    s14 += " : ";
    s14 += *it;
    qDebug() << qPrintable(s14);
}

