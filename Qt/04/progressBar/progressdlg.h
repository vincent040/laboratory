#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#include <QDialog>

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QProgressBar>

class progressDlg : public QDialog
{
    Q_OBJECT

public:
    progressDlg(QWidget *parent = 0);
    ~progressDlg();

private slots:
    void startProgress();

private:
    QLabel *fileNum;
    QLineEdit *fileNumLineEdit;
    QLabel *progressType;
    QComboBox *cmbox;
    QProgressBar *prgBar;
    QPushButton *startBtn;
    QGridLayout *mainLayout;
};

#endif // PROGRESSDLG_H
