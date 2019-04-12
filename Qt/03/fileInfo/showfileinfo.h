#ifndef SHOWFILEINFO_H
#define SHOWFILEINFO_H

#include <QDialog>

#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFileDialog>

namespace Ui {
class showFileInfo;
}

class showFileInfo : public QDialog
{
    Q_OBJECT

public:
    explicit showFileInfo(QWidget *parent = 0);
    ~showFileInfo();

private:
    Ui::showFileInfo *ui;

private:
    QPushButton *fileBtn;
    QLineEdit *fileLineEdit;
    QGridLayout *mainLayout;

private slots:
    void showFile();
};

#endif // SHOWFILEINFO_H
