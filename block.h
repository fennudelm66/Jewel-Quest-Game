#ifndef BLOCK_H
#define BLOCK_H

#include <QPushButton>

class Block : public QPushButton
{
    Q_OBJECT  // 启用 Qt 信号与槽机制

public:
    // 默认构造函数
    Block(QWidget *parent = nullptr,int type = 0)
        : QPushButton(parent), type(type)
    {

        // 可选：设置按钮的默认显示文本或图标等
        this->setText(QString("Block(%1, %2)").arg(x).arg(y));
    }

    // 获取坐标
    int getX() const { return x; }
    int getY() const { return y; }

    // 获取类型
    int getType() const { return type; }

    // 设置类型
    void setType(int newType) { type = newType; }

    // 设置位置
    void setPosition(int newX, int newY)
    {
        x = newX;
        y = newY;
        // // 如果需要，更新按钮的显示文本或位置
        // this->setText(QString("Block(%1, %2)").arg(x).arg(y));
    }

private:
    int type;  // 表示块的类型
    int x, y;  // 坐标
};

#endif // BLOCK_H
