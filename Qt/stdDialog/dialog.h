i#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

/***** 1，标准文件对话框 *****/
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFileDialog>

/***** 2，标准颜色对话框 *****/
#include <QFrame>
#include <QColorDialog>

/***** 3，标准字体对话框 *****/
#include <QFont>
#include <QFontDialog>

/***** 4，标准输入对话框 *****/
#include <QDialog>
#include <QLabel>
#include <QInputDialog>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

/***** 1，标准文件对话框 *****/
private:
    QPushButton *fileBtn;
    QLineEdit *fileLineEdit;
    QGridLayout *mainLayout;

private slots:
    void showFile();


/***** 2，标准颜色对话框 *****/
private:
    QPushButton *colorBtn;
    // QFrame可以用来调整菜单的“浮起”、进度条的“沉入”等效果
    QFrame *colorFrame;

private slots:
    void showColor();


/***** 3，标准字体对话框 *****/
private:
    QPushButton *fontBtn;
    QLineEdit *fontLineEdit;

private slots:
    void showFont();


/***** 4，标准输入对话框 *****/
private:
    QLabel *nameLabel1, *nameLabel2; // string
    QLabel *ageLabel1, *ageLabel2; // int
    QLabel *sexLabel1, *sexLabel2; // char
    QLabel *scoreLabel1, *scoreLabel2; // double

    QPushButton *nameBtn;
    QPushButton *ageBtn;
    QPushButton *sexBtn;
    QPushButton *scoreBtn;

private slots:
    void changeName();
    void changeAge();
    void changeSex();
    void changeScore();


};

#endif // DIALOG_H
