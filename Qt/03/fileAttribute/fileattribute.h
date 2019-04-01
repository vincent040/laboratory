#ifndef FILEATTRIBUTE_H
#define FILEATTRIBUTE_H

#include <QDialog>
#include <QString>

namespace Ui {
class fileAttribute;
}

class fileAttribute : public QDialog
{
    Q_OBJECT

public:
    explicit fileAttribute(QWidget *parent = 0);
    ~fileAttribute();

private:
    Ui::fileAttribute *ui;
    QString fileFullName;
    QString filePath;

private slots:
    void getFileName();
    void getFileAttr();
};

#endif // FILEATTRIBUTE_H
