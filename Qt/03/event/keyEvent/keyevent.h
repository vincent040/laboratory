#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class keyEvent;
}

class keyEvent : public QWidget
{
    Q_OBJECT

public:
    explicit keyEvent(QWidget *parent = 0);
    ~keyEvent();

    void keyPressEvent(QKeyEvent *kpe);

private:
    Ui::keyEvent *ui;
};

#endif // KEYEVENT_H
