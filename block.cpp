#include "Block.h"

Block::Block(QWidget *parent, int type, int x, int y)
    : QPushButton(parent), type(type), x(x), y(y)
{
    // 设置图标
    setBlockIcon();

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
    if (pixmap.isNull()) {
        qDebug() << "Failed to load image: " << iconPath;
    }
    // 缩放图片使其适应指定的大小，保持原始纵横比
    QSize targetSize(40, 40);
    QPixmap scaledPixmap = pixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    this->setIcon(QIcon(scaledPixmap));
    this->setIconSize(targetSize);


    this->setFlat(true);
}
