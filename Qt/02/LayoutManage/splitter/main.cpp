#include "widget.h"
#include <QApplication>
#include <QSplitter>
#include <QTextEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplitter *splitterMain = new QSplitter(Qt::Horizontal, 0);
    QSplitter *splitterLeft = new QSplitter(Qt::Vertical, splitterMain);

    splitterLeft->setOpaqueResize(true);

    QTextEdit *text1= new QTextEdit("左上窗口", splitterLeft);
    text1->setAlignment(Qt::AlignCenter);

    QTextEdit *text2 = new QTextEdit("左下窗口", splitterLeft);
    text2->setAlignment(Qt::AlignHCenter);

    QTextEdit *text3 = new QTextEdit("右窗口", splitterMain);
    text3->setAlignment(Qt::AlignCenter);

    splitterMain->show();

    return a.exec();
}
