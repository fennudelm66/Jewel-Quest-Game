#include "mainwindow.h"
#include "GameModeWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QApplication>
#include <QMainWindow>
#include <QIcon>
#include <QPalette>
#include <QLabel>
#include <QFont>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口大小
    setFixedSize(400, 700);

    // 创建按钮
    QPushButton *startButton = new QPushButton("开始游戏", this);
    QPushButton *rankingButton = new QPushButton("排行榜", this);
    QPushButton *exitButton = new QPushButton("退出游戏", this);

    // 设置按钮样式
    QString buttonStyle = R"(
        QPushButton {
            background-color: yellow;
            color: brown;
            font: bold 16px;
            border-radius: 30px;
            border: 3px solid brown;
            padding: 10px;
            width: 200px;  /* 设置固定宽度 */
            margin: 10px;
        }
        QPushButton:hover {
            color: green;
        }
        QPushButton:pressed {
            color: green;
        }
    )";

    // 应用样式
    startButton->setStyleSheet(buttonStyle);
    rankingButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    // 创建布局并将按钮添加到底部
    QVBoxLayout *layout = new QVBoxLayout;

    // 添加按钮
    layout->addWidget(startButton);
    layout->addWidget(rankingButton);
    layout->addWidget(exitButton);

    startButton->setFixedSize(150,80);  // 设置按钮在窗口内的位置，(50, 50) 是按钮的左上角位置
    rankingButton->setFixedSize(150,80);
    exitButton->setFixedSize(150,80);

    startButton->move(125, 420);
    rankingButton->move(125, 510);
    exitButton->move(125,600);

    // 创建一个标签用于显示标题
    QLabel *titleLabel = new QLabel("消 消 乐", this);

    // 设置字体，艺术感的字体样式
    QFont titleFont("微软雅黑", 40, QFont::Bold);  // 设置字体为“微软雅黑”，大小为36，加粗
    titleFont.setItalic(true);  // 设置字体为斜体
    titleLabel->setFont(titleFont);

    // 设置标签的颜色和样式
    titleLabel->setStyleSheet("color: yellow;");  // 设置文字颜色为番茄红
    layout->addWidget(titleLabel);
    titleLabel->move(100,150);
    titleLabel->setFixedSize(200,200);

    // 创建设置按钮并设置图标
    QPushButton *settingsButton = new QPushButton(this);
    QIcon settingsIcon(":/Settings.png");  // 设置按钮图标
    settingsButton->setIcon(settingsIcon);
    settingsButton->setIconSize(QSize(32, 32));  // 设置图标大小
    settingsButton->setFlat(true);  // 去除按钮的边框和背景

    // 将按钮放置在右上角
    settingsButton->move(width() - settingsButton->width() - 10, 10);

    connect(exitButton, &QPushButton::clicked, this, &MainWindow::onExitClicked);
    connect(startButton,&QPushButton::clicked,this,&MainWindow::onStartClicked);

}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // 这里可以根据需求绘制背景图片
    QPainter painter(this);
    QPixmap background(":/1.jpg");

    if (!background.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background);
    }
    else {
        painter.fillRect(0, 0, width(), height(), Qt::white);
    }

    QMainWindow::paintEvent(event); // 调用基类的 paintEvent
}

void MainWindow::onExitClicked()
{
    QApplication::quit();  // 退出应用程序
}

void MainWindow::onStartClicked()
{
    // 创建并显示 GameModeWindow
    GameModeWindow *gameModeWindow = new GameModeWindow(this);

    // 获取目标位置
    int targetX = (this->width() - gameModeWindow->width()) / 2;
    int targetY = (this->height() - gameModeWindow->height()) / 2;

    // 设置初始位置为屏幕上方
    gameModeWindow->move(targetX, -gameModeWindow->height());

    // 创建透明度效果并应用到窗口
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(gameModeWindow);
    gameModeWindow->setGraphicsEffect(opacityEffect);

    // 创建并配置透明度动画
    QPropertyAnimation *opacityAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    opacityAnimation->setDuration(500);  // 动画持续时间
    opacityAnimation->setStartValue(0.0);  // 初始透明度为 0（完全透明）
    opacityAnimation->setEndValue(1.0);    // 最终透明度为 1（完全不透明）

    // 创建位置动画，使窗口下落
    QPropertyAnimation *positionAnimation = new QPropertyAnimation(gameModeWindow, "pos");
    positionAnimation->setDuration(500);
    positionAnimation->setStartValue(QPoint(targetX, -gameModeWindow->height()));
    positionAnimation->setEndValue(QPoint(targetX, targetY));

    // 并行启动两个动画
    opacityAnimation->start();
    positionAnimation->start();

    // 显示窗口
    gameModeWindow->show();

    // 连接信号与槽
    connect(gameModeWindow, &GameModeWindow::stageModeSelected, this, &MainWindow::onStageModeSelected);
    connect(gameModeWindow, &GameModeWindow::endlessModeSelected, this, &MainWindow::onEndlessModeSelected);
}

void MainWindow::onStageModeSelected()
{
    // 处理闯关模式的逻辑
    // 比如切换到闯关模式的界面
    qDebug() << "闯关模式选中!";
}

void MainWindow::onEndlessModeSelected()
{
    // 处理无尽模式的逻辑
    // 比如切换到无尽模式的界面
    qDebug() << "无尽模式选中!";
}