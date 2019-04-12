#include "msgboxdlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    msgBoxDlg w;
    w.show();

    return a.exec();
}
