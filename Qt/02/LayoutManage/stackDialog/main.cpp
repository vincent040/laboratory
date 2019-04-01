#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog *dlg = new Dialog();
    dlg->show();

    return a.exec();
}
