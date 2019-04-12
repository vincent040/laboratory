#include "progressdlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    progressDlg w;
    w.show();

    return a.exec();
}
