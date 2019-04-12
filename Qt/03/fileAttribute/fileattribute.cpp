#include "fileattribute.h"
#include "ui_fileattribute.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

fileAttribute::fileAttribute(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileAttribute)
{
    ui->setupUi(this);

    connect(ui->btnFile, SIGNAL(clicked(bool)),
            this, SLOT(getFileName()));

    connect(ui->btnGetFileAttr, SIGNAL(clicked(bool)),
            this, SLOT(getFileAttr()));
}

fileAttribute::~fileAttribute()
{
    delete ui;
}

void fileAttribute::getFileName()
{
    QString searchPath;
    if(filePath.length() == 0)
        searchPath = "/";
    else
        searchPath = filePath;

    fileFullName = QFileDialog::getOpenFileName(this, "选择文件",
                                         searchPath, "files(*)");
    QFileInfo info(fileFullName);
    filePath = info.absolutePath();

    ui->lineEditFilename->setText(info.baseName());
}

void fileAttribute::getFileAttr()
{
    QFileInfo info(fileFullName); // 获取文件的属性信息

    if(!info.exists())
    {
        qDebug() << "文件不存在";
        return;
    }

    // 获取文件的大小
    qint64 size = info.size();
    ui->labelSize->setText(QString::number(size));

    // 获取文件的时间戳
    QDateTime dt;
    dt = info.created();
    ui->labelCreate->setText(dt.toString());

    dt = info.lastModified();
    ui->labelModify->setText(dt.toString());

    // 获取文件的权限
    bool isDir = info.isDir();
    bool isReg = info.isFile();
    bool isLnk = info.isSymLink();
    bool isRnd = info.isReadable();
    bool isWri = info.isWritable();
    bool isExc = info.isExecutable();

    ui->checkBoxDir->setCheckState(isDir ? Qt::Checked : Qt::Unchecked);
    ui->checkBoxFile->setCheckState(isReg ? Qt::Checked : Qt::Unchecked);
    ui->checkBoxLink->setCheckState(isLnk ? Qt::Checked : Qt::Unchecked);
    ui->checkBoxRead->setCheckState(isRnd ? Qt::Checked : Qt::Unchecked);
    ui->checkBoxWrite->setCheckState(isWri ? Qt::Checked : Qt::Unchecked);
    ui->checkBoxExec->setCheckState(isExc ? Qt::Checked : Qt::Unchecked);
}


