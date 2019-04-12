#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#include <QDialog>

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QProgressBar>
#include <QProgressDialog>
#include "worker.h"

class progressDlg : public QDialog
{
    Q_OBJECT

public:
    progressDlg(QWidget *parent = 0);
    ~progressDlg();

private slots:
    void startProgress();

    void progress1(int percent);
    void progress2(int percent);

private:
    QLabel *fileNum;
    QLineEdit *fileNumLineEdit;
    QLabel *progressType;
    QComboBox *cmbox;
    QProgressBar *prgBar;
    QPushButton *startBtn;
    QGridLayout *mainLayout;
    QProgressDialog *prgDlg;

    worker *worker1;
    int totalJobs;
};

#endif // PROGRESSDLG_H
