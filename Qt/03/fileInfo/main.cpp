#include "showfileinfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    showFileInfo w;
    w.show();

    return a.exec();
}
