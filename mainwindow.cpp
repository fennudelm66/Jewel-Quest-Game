#include "mainwindow.h"
#include "GameModeWindow.h"
#include "LevelSelectWindow.h"
#include "EndlessModeWindow.h"
#include "GameSettingsWindow.h"
#include "levelgame.h"
#include "audiomanager.h"
#include "historywindow.h"

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
#include <QSoundEffect>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
       audioManager(new AudioManager(this)),  // 创建 AudioManager 实例
       soundEnabled(true),                   // 默认启用音效
       currentVolume(50)                     // 默认音量 50%

{   // 设置初始音量和播放背景音乐
    audioManager->loadBackgroundMusic("gameMusic", "qrc:/n/music/music-2.wav");
    audioManager->playBackgroundMusic("gameMusic");
    audioManager->setGlobalVolume(currentVolume / 100.0f);
    audioManager->setSoundEnabled(soundEnabled);

    // 设置窗口大小
    setFixedSize(500, 800);

    // 创建按钮
    QPushButton *startButton = new QPushButton("开始游戏", this);
    QPushButton *rankingButton = new QPushButton("历史记录", this);
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

    startButton->move(175, 470);
    rankingButton->move(175, 560);
    exitButton->move(175,650);

    // 创建一个标签用于显示标题
    QLabel *titleLabel = new QLabel("消 消 乐", this);

    // 设置字体，艺术感的字体样式
    QFont titleFont("微软雅黑", 40, QFont::Bold);  // 设置字体为“微软雅黑”，大小为36，加粗
    titleFont.setItalic(true);  // 设置字体为斜体
    titleLabel->setFont(titleFont);

    // 设置标签的颜色和样式
    titleLabel->setStyleSheet("color: yellow;");  // 设置文字颜色为番茄红
    layout->addWidget(titleLabel);
    titleLabel->move(150,150);
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
    connect(rankingButton,&QPushButton::clicked,this,&MainWindow::onRankingClicked);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::onSettingClicked);


}


MainWindow::~MainWindow() {

}

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
    // 创建并显示关卡选择弹窗
    LevelSelectWindow *levelSelectWindow = new LevelSelectWindow(this);

    // 获取主窗口的中心位置，计算弹窗的居中位置
    int targetX = (this->width() - levelSelectWindow->width()) / 2;
    int targetY = (this->height() - levelSelectWindow->height()) / 2;

    // 设置弹窗显示的位置
    levelSelectWindow->move(targetX, targetY);

    // 显示关卡选择窗口
    levelSelectWindow->show();

    // 连接信号与槽
    connect(levelSelectWindow, &LevelSelectWindow::levelSelected, this, &MainWindow::onLevelSelected);
}

void MainWindow::onLevelSelected(int level)
{
    qDebug() << "选中的关卡是:" << level;

    // 关闭关卡选择窗口
    LevelSelectWindow *senderWindow = qobject_cast<LevelSelectWindow*>(sender());
    if (senderWindow) {
        senderWindow->close();
    }

    // 传递关卡信息，启动游戏主画面
    startGame(level);
}

void MainWindow::startGame(int level)
{
    // 在这里根据关卡编号进行游戏初始化，可以跳转到新的游戏界面
    qDebug() << "开始游戏，当前关卡是: " << level;
    // 根据选中的关卡传递给新窗口并初始化

    this->hide();
    LevelGame *levelgame = new LevelGame(level, nullptr); // 将level传递给新的窗口
    levelgame->show();
}

void MainWindow::onRankingClicked()
{
    // 创建历史记录窗口
    HistoryWindow *historyWindow = new HistoryWindow(this);


    // 获取主窗口的位置和大小
    QRect mainWindowGeometry = this->geometry();
    int mainWindowCenterX = mainWindowGeometry.center().x();
    int mainWindowCenterY = mainWindowGeometry.center().y();

    // 获取历史窗口的大小
    QRect historyWindowGeometry = historyWindow->geometry();
    int historyWindowWidth = historyWindowGeometry.width();
    int historyWindowHeight = historyWindowGeometry.height();

    // 计算历史窗口的左上角位置，使其居中
    int x = mainWindowCenterX - historyWindowWidth / 2;
    int y = mainWindowCenterY - historyWindowHeight / 2;

    // 设置历史窗口的位置
    historyWindow->move(x, y);

    // 创建透明度效果对象
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(historyWindow);
    historyWindow->setGraphicsEffect(opacityEffect);

    // 创建动画对象，控制透明度
    QPropertyAnimation *fadeAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    fadeAnimation->setDuration(500);  // 设置动画时长为 1 秒
    fadeAnimation->setStartValue(0.0); // 起始透明度为 0（完全透明）
    fadeAnimation->setEndValue(1.0);   // 结束透明度为 1（完全不透明）
    // 显示历史窗口
    historyWindow->show();
    // 启动动画
    fadeAnimation->start();
}

void MainWindow::onEndlessModeSelected()
{
    qDebug() << "限时模式选中!";

    // 隐藏当前窗口
    this->hide();

    // 创建并显示新的窗口
    EndlessModeWindow *endlessWindow = new EndlessModeWindow(nullptr);
    endlessWindow->show();
}

void MainWindow::onSettingClicked()
{

    // 创建并显示 SettingsWindow
    GameSettingsWindow *settingsWindow = new GameSettingsWindow(this,audioManager);//传递audioManager实例

    // 获取目标位置
    int targetX = (this->width() - settingsWindow->width()) / 2;
    int targetY = (this->height() - settingsWindow->height()) / 2;

    // 设置初始位置为屏幕上方
    settingsWindow->move(targetX, -settingsWindow->height());

    // 创建透明度效果并应用到窗口
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(settingsWindow);
    settingsWindow->setGraphicsEffect(opacityEffect);

    // 创建并配置透明度动画
    QPropertyAnimation *opacityAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    opacityAnimation->setDuration(500);  // 动画持续时间
    opacityAnimation->setStartValue(0.0);  // 初始透明度为 0（完全透明）
    opacityAnimation->setEndValue(1.0);    // 最终透明度为 1（完全不透明）

    // 创建位置动画，使窗口下落
    QPropertyAnimation *positionAnimation = new QPropertyAnimation(settingsWindow, "pos");
    positionAnimation->setDuration(500);
    positionAnimation->setStartValue(QPoint(targetX, -settingsWindow->height()));
    positionAnimation->setEndValue(QPoint(targetX, targetY));

    // 并行启动两个动画
    opacityAnimation->start();
    positionAnimation->start();

    // 显示历史窗口
    settingsWindow->show();
}
