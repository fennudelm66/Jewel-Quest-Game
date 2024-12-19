#ifndef BLOCK_H
#define BLOCK_H

#include <QPushButton>
#include <QPixmap>
#include <QIcon>

class Block : public QPushButton
{
    Q_OBJECT  // 启用 Qt 信号与槽机制

public:
    // 默认构造函数
    Block(QWidget *parent = nullptr, int type = 0, int x = 0, int y = 0);

    // 获取棋子坐标
    int getX() const;
    int getY() const;

    // 改变棋子位置
    void setPosition(int newX, int newY);

    // 获取棋子类型
    int getType() const;

    // 设置棋子类型
    void setType(int newType);

private:
    int type;  // 宝石或道具类型
    int x, y;  // 坐标

    // 设置图标
    void setBlockIcon();
};

#endif // BLOCK_H
