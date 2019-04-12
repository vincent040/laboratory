#include "keyevent.h"
#include "ui_keyevent.h"
#include <QDebug>

keyEvent::keyEvent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::keyEvent)
{
    ui->setupUi(this);

}

keyEvent::~keyEvent()
{
    delete ui;
}

void keyEvent::keyPressEvent(QKeyEvent *kpe)
{
    qDebug() << "[" << char(kpe->key()) << "]"
             << hex << "0x" << kpe->key()
             << "," << dec  << kpe->key();

    if(kpe->modifiers() == Qt::ShiftModifier)
    {
        switch(kpe->key())
        {
        case Qt::Key_Minus: qDebug() << ")"; break;
        case Qt::Key_plusminus: qDebug() << "!"; break;
        case Qt::Key_At: qDebug() << "@"; break;
        case Qt::Key_Colon: qDebug() << ";"; break;
        case Qt::Key_Comma: qDebug() << ":"; break;
        }
    }

    switch(kpe->key())
    {
    case Qt::Key_0: qDebug() << 0; break;
    case Qt::Key_1: qDebug() << 1; break;
    case Qt::Key_2: qDebug() << 2; break;
    case Qt::Key_3: qDebug() << 3; break;
    }
}
