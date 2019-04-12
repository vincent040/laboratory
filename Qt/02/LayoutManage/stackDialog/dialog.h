#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QStackedWidget>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    QStackedWidget *stack; // 堆叠窗体

    QListWidget *list;

    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
};

#endif // DIALOG_H
