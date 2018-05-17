#include "httpinfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HttpInfo w;
    w.show();

    return a.exec();
}
