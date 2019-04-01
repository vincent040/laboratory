#ifndef MSGBOXDLG_H
#define MSGBOXDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui {
class msgBoxDlg;
}

class msgBoxDlg : public QDialog
{
    Q_OBJECT

public:
    explicit msgBoxDlg(QWidget *parent = 0);
    ~msgBoxDlg();

private slots:
    void showQuestionMsg();

private:
    QLabel *label;

    QPushButton *questionBtn;

    QVBoxLayout *mainLayout;
};

#endif // MSGBOXDLG_H
