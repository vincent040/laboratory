#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    e = new example;

    // 任意权限的槽函数，都可以被外部对象的信号触发
    // 因为信号触发槽函数时，会调用槽函数所在类的一个特殊函数
    // 这个特殊函数可以调用槽函数所在类的所有权限的槽函数
    connect(ui->pushButton, SIGNAL(clicked(bool)),
            e, SLOT(privateSlot()));

    connect(ui->pushButton, SIGNAL(clicked(bool)),
            e, SLOT(protectedSlot()));

    connect(ui->pushButton, SIGNAL(clicked(bool)),
            e, SLOT(publicSlot()));

    // 如果直接调用类对象的槽函数，那么此时的槽函数就跟普通函数没啥区别
    // 能否调用将会受到该槽函数在类中的权限的限制
    // 因此，此时无法调用私有和保护类型的槽函数，只能调用公有槽函数
//    e->privateSlot();
//    e->protectedSlot();
    e->publicFunc();
}

MainWindow::~MainWindow()
{
    delete ui;
}
