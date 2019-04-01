#include "tcpsrv.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale();
    tcpSrv w;
    w.show();

    return a.exec();
}
