#include "Block.h"

Block::Block(QWidget *parent, int type, int x, int y)
    : QPushButton(parent), type(type), x(x), y(y)
{
    // 设置图标
    setBlockIcon();

    // 可选：设置按钮的默认显示文本或图标等
    this->setText(QString("Block(%1, %2)").arg(x).arg(y));
}

// 获取棋子坐标
int Block::getX() const
{
    return x;
}

int Block::getY() const
{
    return y;
}

// 改变棋子位置
void Block::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
    // 更新按钮文本
    this->setText(QString("Block(%1, %2)").arg(x).arg(y));
}

// 获取棋子类型
int Block::getType() const
{
    return type;
}

// 设置棋子类型
void Block::setType(int newType)
{
    type = newType;
    setBlockIcon();  // 更新图标
}

// 设置图标
void Block::setBlockIcon()
{
    QString iconPath;

    // 根据类型设置对应的图标路径
    switch (type) {
    case 0:
        iconPath = ":/gem0.png";  // type 0 图标
        break;
    case 1:
        iconPath = ":/gem1.png";  // type 1 图标
        break;
    case 2:
        iconPath = ":/gem2.png";  // type 2 图标
        break;
    // 添加更多类型及其图标路径
    default:
        iconPath = ":/default.png";  // 默认图标
        break;
    }

    // 使用图标路径设置按钮的图标
    QPixmap pixmap(iconPath);
    this->setIcon(QIcon(pixmap));
    this->setIconSize(pixmap.size());  // 设置图标大小为图片原始大小
    this->setFlat(true);
}
