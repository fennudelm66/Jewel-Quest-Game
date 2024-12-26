#include "GameSettingsWindow.h"
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QPainter>
#include <QPixmap>

GameSettingsWindow::GameSettingsWindow(QWidget *parent, AudioManager *audioMgr)
    : QWidget(parent),
    audioManager(audioMgr),  // 通过构造函数传递 AudioManager
    soundEnabled(true),
    currentVolume(50)  // 默认音量50%
{
    // 设置窗口大小
    setFixedSize(400, 300);

    // 创建关闭按钮
    closeButton = new QPushButton("×", this);
    closeButton->setStyleSheet("background-color: transparent; color: white; font: bold 20px;");
    closeButton->setFixedSize(30, 30);
    closeButton->move(350, 80);  // 设置关闭按钮位置（右上角）

    // 创建音效开关按钮
    QPushButton *soundToggleButton = new QPushButton("音效开关", this);
    soundToggleButton->setStyleSheet("background-color: yellow; color: brown; font: bold 16px;");
    soundToggleButton->setFixedSize(120, 45);
    soundToggleButton->move(140, 100);  // 设置音效开关按钮的位置

    // 创建恢复默认按钮
    QPushButton *resetButton = new QPushButton("恢复默认", this);
    resetButton->setStyleSheet("background-color: yellow; color: brown; font: bold 16px;");
    resetButton->setFixedSize(120, 45);
    resetButton->move(140, 160);  // 设置恢复默认按钮的位置

    // 创建音量调节条
    QSlider *volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);  // 设置音量范围 0-100
    volumeSlider->setValue(currentVolume);  // 设置初始音量值
    volumeSlider->setStyleSheet("QSlider {background: yellow;}");

    // 创建音量标签
    QLabel *volumeLabel = new QLabel("音量", this);
    volumeLabel->setStyleSheet("color: yellow; font: bold 20px;");


    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(50, 90, 50, 50);  // 设置内边距，让元素不会贴边
    layout->setSpacing(20);  // 设置控件之间的间隔

    layout->addWidget(soundToggleButton,0, Qt::AlignCenter);
    layout->addWidget(resetButton,0, Qt::AlignCenter);
    layout->addWidget(volumeLabel);
    layout->addWidget(volumeSlider);
    setLayout(layout);

    // 按钮和音量控制绑定
    connect(soundToggleButton, &QPushButton::clicked, this, &GameSettingsWindow::toggleSound);
    connect(resetButton, &QPushButton::clicked, this, &GameSettingsWindow::resetSettings);
    connect(volumeSlider, &QSlider::valueChanged, this, &GameSettingsWindow::updateVolume);
    // 连接关闭按钮的槽
    connect(closeButton, &QPushButton::clicked, this, &GameSettingsWindow::closeWindow);

    // 初始化音效
    if (audioManager) {
        audioManager->loadBackgroundMusic("gameMusic", "qrc:/n/music/music-2.wav");
        audioManager->playBackgroundMusic("gameMusic");
        audioManager->setGlobalVolume(currentVolume / 100.0f);
        audioManager->setSoundEnabled(soundEnabled);
    }
}

// 绘制背景图片
void GameSettingsWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap background(":/PopupBackground.png");  // 加载背景图片

    // 绘制背景图
    painter.drawPixmap(0, 0, width(), height(), background);  // 让背景图适应窗口大小
}

// 音效开关
void GameSettingsWindow::toggleSound()
{
    soundEnabled = !soundEnabled;
    if (audioManager) {
        audioManager->setSoundEnabled(soundEnabled);
    }
}

// 恢复默认设置
void GameSettingsWindow::resetSettings()
{
    soundEnabled = true;
    currentVolume = 50;
    if (audioManager) {
        audioManager->setSoundEnabled(soundEnabled);
        audioManager->setGlobalVolume(currentVolume / 100.0f);
    }
}

// 更新音量
void GameSettingsWindow::updateVolume(int volume)
{
    currentVolume = volume;
    if (audioManager) {
        audioManager->setGlobalVolume(currentVolume / 100.0f);
    }
}

// 关闭窗口
void GameSettingsWindow::closeWindow()
{
    close();  // 关闭窗口
}
