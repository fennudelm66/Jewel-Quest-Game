#include "InputManager.h"

// 构造函数，初始化鼠标和键盘输入状态
InputManager::InputManager(QObject *parent)
    : QObject(parent), mouseEnabled(true), keyboardEnabled(true) {}

// 启用或禁用鼠标输入
void InputManager::setMouseEnabled(bool enabled) {
    mouseEnabled = enabled;
}

// 启用或禁用键盘输入
void InputManager::setKeyboardEnabled(bool enabled) {
    keyboardEnabled = enabled;
}

// 事件过滤器，拦截鼠标和键盘事件
bool InputManager::eventFilter(QObject *obj, QEvent *event) {
    if (mouseEnabled && event->type() == QEvent::MouseButtonPress) {  // 如果启用了鼠标输入并检测到鼠标按下
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);  // 转换为鼠标事件
        emit mouseClicked(mouseEvent->x(), mouseEvent->y());  // 触发鼠标点击信号
        return true;  // 表示事件已处理
    }

    if (keyboardEnabled && event->type() == QEvent::KeyPress) {  // 如果启用了键盘输入并检测到按键按下
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);  // 转换为键盘事件
        emit keyPressed(keyEvent->key());  // 触发按键按下信号
        return true;  // 表示事件已处理
    }

    return QObject::eventFilter(obj, event);  // 未处理的事件继续传递
}
