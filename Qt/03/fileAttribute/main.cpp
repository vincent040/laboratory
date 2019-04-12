#include "fileattribute.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fileAttribute w;
    w.show();

    return a.exec();
}
