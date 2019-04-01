#include "udpsrv.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    udpSrv w;
    w.show();

    return a.exec();
}
