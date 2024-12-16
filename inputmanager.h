#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <QObject>
#include <QEvent>
#include <QMouseEvent>  // 处理鼠标事件
#include <QKeyEvent>  // 处理键盘事件

// InputManager 类用于用户输入鼠标和键盘
class InputManager : public QObject {
    Q_OBJECT

public:
    explicit InputManager(QObject *parent = nullptr);

    void setMouseEnabled(bool enabled);  // 设置是否用鼠标输入
    void setKeyboardEnabled(bool enabled);  // 设置是否用键盘输入

signals:
    void mouseClicked(int x, int y);  // 鼠标点击信号，传递点击位置
    void keyPressed(int key);  // 按键按下信号，传递按键值

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;  // 事件过滤器处理事件分发

private:
    bool mouseEnabled;  // 是否启用鼠标输入
    bool keyboardEnabled;  // 是否启用键盘输入
};

#endif // INPUTMANAGER_H
