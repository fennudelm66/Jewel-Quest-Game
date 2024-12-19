#ifndef BLOCK_H
#define BLOCK_H

#include <QPushButton>

class Block : public QPushButton
{
    Q_OBJECT  // 启用 Qt 信号与槽机制

public:
    // 默认构造函数
    Block(QWidget *parent = nullptr, int x = -1, int y = -1, int type = 0)
        : QPushButton(parent), x(x), y(y), type(type)
    {
        // 可选：设置按钮的默认显示文本或图标等
        this->setText(QString("Block(%1, %2)").arg(x).arg(y));
    }

    // 获取棋子坐标
    int getX() const { return x; }
    int getY() const { return y; }

    // 改变棋子位置
    void setPosition(int newX, int newY)
    {
        x = newX;
        y = newY;
        // 可选：更新按钮文本
        this->setText(QString("Block(%1, %2)").arg(x).arg(y));
    }

    // 获取棋子类型
    int getType() const { return type; }

    // 设置棋子类型
    void setType(int newType) { type = newType; }

private:
    int type;  // 宝石或道具类型
    int x, y;  // 坐标
};

#endif // BLOCK_H

