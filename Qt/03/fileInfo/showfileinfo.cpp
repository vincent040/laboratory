#include "showfileinfo.h"
#include "ui_showfileinfo.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

showFileInfo::showFileInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showFileInfo)
{
    ui->setupUi(this);

    fileBtn = new QPushButton("选择文件");
    fileLineEdit = new QLineEdit;

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(fileBtn, 0, 0);
    mainLayout->addWidget(fileLineEdit, 0, 1);

    mainLayout->addWidget(ui->plainTextEdit, 1, 0, 10, 2);

    connect(fileBtn, SIGNAL(clicked(bool)),
            this, SLOT(showFile()));
}

showFileInfo::~showFileInfo()
{
    delete ui;
}


void showFileInfo::showFile()
{
    QString files;
    files += "源码(*.cpp *.c *cxx);;";
    files += "头文件(*.h *.hpp);;";
    files += "所有文件(*)";

    QString s = QFileDialog::getOpenFileName(this, "打开文件", "/", files);
    fileLineEdit->setText(s);

    QFile ifile(s);
    if(ifile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream f(&ifile);

        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(f.readAll());
    }
    else
            qDebug() << ifile.errorString() << endl;


}
