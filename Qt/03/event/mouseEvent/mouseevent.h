#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QMainWindow>

#include <QLabel>
#include <QStatusBar>
#include <QMouseEvent>

namespace Ui {
class mouseEvent;
}

class mouseEvent : public QMainWindow
{
    Q_OBJECT

public:
    explicit mouseEvent(QWidget *parent = 0);
    ~mouseEvent();

protected:
    // 复写从QMainWindow中继承下来的鼠标响应函数
    void mousePressEvent(QMouseEvent *e); // 按下
    void mouseMoveEvent(QMouseEvent *e);  // 移动
    void mouseReleaseEvent(QMouseEvent *e);    // 松开
    void mouseDoubleClickEvent(QMouseEvent *e);// 双击

private:
    Ui::mouseEvent *ui;

    // 将两个标签放置到当前主窗口的下方作为状态栏
    QLabel *status;
    QLabel *position;
};

#endif // MOUSEEVENT_H
