// LevelSelectWindow.cpp
#include "LevelSelectWindow.h"
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

LevelSelectWindow::LevelSelectWindow(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口为无边框，背景透明
    setWindowFlags(Qt::FramelessWindowHint);

    // 设置背景图
    setAutoFillBackground(true);

    // 设置窗口属性为透明背景
    setAttribute(Qt::WA_TranslucentBackground);


    // 布局管理
    layout = new QVBoxLayout(this);

    // 设置按钮之间的间距
    layout->setSpacing(8);  // 设置按钮之间的间距

    // 设置布局的边距（上下左右的边距）
    layout->setContentsMargins(100, 110, 0, 0);  // 设置上边距为30，其他边距为0



    // 创建关卡选择按钮
    for (int i = 1; i <= 4; ++i) {
        QPushButton *button = new QPushButton(QString("关卡 %1").arg(i), this);
        layout->addWidget(button);
        button->setStyleSheet("background-color: yellow; color: brown; font: bold 16px;");
        button->setFixedSize(120,50);
        connect(button, &QPushButton::clicked, this, [this, i]() {
            emit levelSelected(i);  // 发射关卡选择信号
        });
    }

    // 设置窗口大小
    setFixedSize(300, 400);  // 可调整大小

    // 为动画准备透明度效果
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(opacityEffect);
    QPropertyAnimation *opacityAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    opacityAnimation->setDuration(500);  // 动画持续时间
    opacityAnimation->setStartValue(0.0);  // 初始透明度为0
    opacityAnimation->setEndValue(1.0);    // 结束透明度为1
    opacityAnimation->start();
}

// 定义槽函数
void LevelSelectWindow::onLevelButtonClicked(int level)
{
    qDebug() << "关卡 " << level << " 被点击";
    emit levelSelected(level);
}

void LevelSelectWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap background(":/PopupBackground.png");  // 加载背景图片

    // 设置透明背景
    painter.setOpacity(1.0);  // 设置完全不透明的背景图
    painter.drawPixmap(0, 0, width(), height(), background);  // 让背景图适应整个窗口大小
}
