#include "udpcli.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    udpCli w;
    w.show();

    return a.exec();
}
