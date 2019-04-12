#include "showtime.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowTime w;
    w.show();

    return a.exec();
}
