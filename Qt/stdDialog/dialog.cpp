#include "dialog.h"
#include <QHBoxLayout>
#include <QStringList>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    /***** 1，标准文件对话框 *****/
    fileBtn = new QPushButton("标准文件对话框");
    fileLineEdit = new QLineEdit;

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(fileBtn, 0, 0);
    mainLayout->addWidget(fileLineEdit, 0, 1);

    connect(fileBtn, SIGNAL(clicked(bool)),
            this, SLOT(showFile()));


    /***** 2，标准颜色对话框 *****/
    colorBtn = new QPushButton("标准颜色对话框");
    // QFrame可以用来调整菜单的“浮起”、进度条的“沉入”等效果
    colorFrame = new QFrame;
    colorFrame->setFrameShape(QFrame::StyledPanel);
    colorFrame->setFrameShadow(QFrame::Sunken);
    colorFrame->setLineWidth(3);
    colorFrame->setAutoFillBackground(true);

    mainLayout->addWidget(colorBtn, 1, 0);
    mainLayout->addWidget(colorFrame, 1, 1);

    connect(colorBtn, SIGNAL(clicked(bool)),
            this, SLOT(showColor()));


    /***** 3，标准字体对话框 *****/
    fontBtn = new QPushButton("标准字体对话框");
    fontLineEdit = new QLineEdit;

    mainLayout->addWidget(fontBtn, 2, 0);
    mainLayout->addWidget(fontLineEdit, 2, 1);

    connect(fontBtn, SIGNAL(clicked(bool)),
            this, SLOT(showFont()));


    /***** 4，标准输入对话框 *****/
    // 4.1 字符串输入
    nameLabel1 = new QLabel("姓名");
    nameLabel1->setAlignment(Qt::AlignCenter);
    nameLabel2 = new QLabel("张三疯");
    nameLabel2->setAlignment(Qt::AlignCenter);
    nameLabel2->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    nameBtn = new QPushButton("修改姓名");

    // 增加一个临时水平布局
    QHBoxLayout *inputLayout1 = new QHBoxLayout;
    mainLayout->addLayout(inputLayout1, 3, 0, 1, 2); // 占1行2列

    inputLayout1->addWidget(nameLabel1);
    inputLayout1->addWidget(nameLabel2);
    inputLayout1->addWidget(nameBtn);

    connect(nameBtn, SIGNAL(clicked(bool)),
            this, SLOT(changeName()));


    // 4.2 整数输入
    ageLabel1 = new QLabel("年龄");
    ageLabel1->setAlignment(Qt::AlignCenter);
    ageLabel2 = new QLabel("19");
    ageLabel2->setAlignment(Qt::AlignCenter);
    ageLabel2->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    ageBtn = new QPushButton("修改年龄");

    QHBoxLayout *inputLayout2 = new QHBoxLayout;
    mainLayout->addLayout(inputLayout2, 4, 0, 1, 2);

    inputLayout2->addWidget(ageLabel1);
    inputLayout2->addWidget(ageLabel2);
    inputLayout2->addWidget(ageBtn);

    connect(ageBtn, SIGNAL(clicked(bool)),
            this, SLOT(changeAge()));

    // 4.3 字符输入
    sexLabel1 = new QLabel("性别");
    sexLabel1->setAlignment(Qt::AlignCenter);
    sexLabel2 = new QLabel("男");
    sexLabel2->setAlignment(Qt::AlignCenter);
    sexLabel2->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    sexBtn = new QPushButton("修改性别");

    QHBoxLayout *inputLayout3 = new QHBoxLayout;
    mainLayout->addLayout(inputLayout3, 5, 0, 1, 2);

    inputLayout3->addWidget(sexLabel1);
    inputLayout3->addWidget(sexLabel2);
    inputLayout3->addWidget(sexBtn);

    connect(sexBtn, SIGNAL(clicked(bool)),
            this, SLOT(changeSex()));

    // 4.4 实数输入
    scoreLabel1 = new QLabel("分数");
    scoreLabel1->setAlignment(Qt::AlignCenter);
    scoreLabel2 = new QLabel("88.5");
    scoreLabel2->setAlignment(Qt::AlignCenter);
    scoreLabel2->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    scoreBtn = new QPushButton("修改分数");

    QHBoxLayout *inputLayout4 = new QHBoxLayout;
    mainLayout->addLayout(inputLayout4, 6, 0, 1, 2);

    inputLayout4->addWidget(scoreLabel1);
    inputLayout4->addWidget(scoreLabel2);
    inputLayout4->addWidget(scoreBtn);

    connect(scoreBtn, SIGNAL(clicked(bool)),
            this, SLOT(changeScore()));
}

Dialog::~Dialog()
{
}

void Dialog::showFile()
{
    QString files;
    files += "源码(*.cpp *.c *cxx);;";
    files += "头文件(*.h *.hpp);;";
    files += "所有文件(*)";

    QString s = QFileDialog::getOpenFileName(this, "打开文件", "/", files);
    fileLineEdit->setText(s);
}

void Dialog::showColor()
{
    // 弹出来调色盘对话框，并将用户选择的颜色赋给c
    QColor c = QColorDialog::getColor(Qt::blue);

    // 如果用户选择了“取消”，则会返回一个非法的颜色值
    if(c.isValid())
    {
        colorFrame->setPalette(QPalette(c));
    }
}

void Dialog::showFont()
{
    // 弹出来字体选择对话框，将所有的属性赋值给f
    bool ok;
    QFont f = QFontDialog::getFont(&ok);

    if(ok)
    {
        fontLineEdit->setFont(f);
    }
}

void Dialog::changeName()
{
    // 调出输入对话框
    bool ok;
    QString text = QInputDialog::getText(this,
                                         "标准字符串输入对话框",
                                         "请输入姓名：",
                                         QLineEdit::Normal,
                                         nameLabel2->text(),
                                         &ok);
    if(ok && !text.isEmpty())
    {
        nameLabel2->setText(text);
    }
}

void Dialog::changeAge()
{
    bool ok;
    int age = QInputDialog::getInt(this,
                                   "标准证书输入对话框",
                                   "请输入年龄",
                                   ageLabel2->text().toInt(&ok),
                                   1, 100, 1, // 最小值、最大值、步长
                                   &ok);
    if(ok)
    {
        QString ageStr;
        ageLabel2->setText(ageStr.setNum(age));
    }
}

void Dialog::changeSex()
{
    QStringList sexList;
    sexList << "男";
    sexList << "女";

    bool ok;
    QString sex = QInputDialog::getItem(this, "标准条目选择对话框",
                                        "请选择性别：",
                                        sexList,
                                        0,
                                        // 改成自动判断当前性别：
                                        //sexList.indexOf(sexLabel2->text()),
                                        true,
                                        &ok);
    if(ok && !sex.isEmpty())
    {
        sexLabel2->setText(sex);
    }
}

void Dialog::changeScore()
{
    bool ok;
    double score = QInputDialog::getDouble(this, "标准实数输入对话框",
                                           "请输入分数",
                                           scoreLabel2->text().toDouble(),
                                           0, 100, 3, // 最大最小值、精度
                                           &ok);
    if(ok)
    {
        QString scoreStr;
        scoreLabel2->setText(scoreStr.setNum(score));
    }
}
