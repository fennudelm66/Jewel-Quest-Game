#include "GameSettingsWindow.h"
#include "qapplication.h"
#include <QPainter>
#include <QPixmap>
#include <QScreen>


// 构造函数
GameSettingsWindow::GameSettingsWindow(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(400, 300);  // 设置窗口大小


    // 设置窗口透明背景
    setAutoFillBackground(true);
    setAttribute(Qt::WA_TranslucentBackground);

    // 创建音量标签
    volumeLabel = new QLabel("音量调节:", this);
    volumeLabel->setStyleSheet("color: white; font: bold 16px;");
    volumeLabel->move(40, 235);

    // 创建音量滑块
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);
    volumeSlider->setGeometry(150, 235, 200, 20);

    // 创建音效开关按钮
    toggleSoundButton = new QPushButton("关闭音效", this);
    toggleSoundButton->setStyleSheet("background-color: yellow; color: brown; font: bold 16px;");
    toggleSoundButton->setFixedSize(120, 40);
    toggleSoundButton->move(140, 100);

    // 创建恢复默认按钮
    resetSettingsButton = new QPushButton("恢复默认", this);
    resetSettingsButton->setStyleSheet("background-color: yellow; color: brown; font: bold 16px;");
    resetSettingsButton->setFixedSize(120, 40);
    resetSettingsButton->move(140, 160);

    // 创建关闭按钮
    closeButton = new QPushButton("\u00d7", this);
    closeButton->setStyleSheet("background-color: transparent; color: white; font: bold 20px;");
    closeButton->setFixedSize(30, 30);
    closeButton->move(350, 80);

    // 创建静音按钮并设置图标
    QPushButton *muteButton = new QPushButton(this);
    muteButton->setIcon(QIcon(":/MuteIcon.png"));  // 设置静音图标
    muteButton->setIconSize(QSize(32, 32));       // 设置图标大小
    muteButton->setFlat(true);                    // 去除按钮边框

    // 将静音按钮放置在音量调节条的右侧
    muteButton->move(volumeSlider->geometry().right() + 10, volumeSlider->geometry().top());


    // 连接信号与槽
    connect(closeButton, &QPushButton::clicked, this, &GameSettingsWindow::close);
    connect(toggleSoundButton, &QPushButton::clicked, this, &GameSettingsWindow::onToggleSoundClicked);
    connect(resetSettingsButton, &QPushButton::clicked, this, &GameSettingsWindow::onResetSettingsClicked);
    connect(volumeSlider, &QSlider::valueChanged, this, &GameSettingsWindow::onVolumeChanged);
    connect(muteButton, &QPushButton::clicked, this, &GameSettingsWindow::onMuteClicked);
}

// 绘制背景
void GameSettingsWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // 标记 event 参数未使用，避免警告

    QPainter painter(this);
    QPixmap background(":/PopupBackground.png"); // 加载背景图片

    // 设置透明背景
    painter.setOpacity(1.0);
    painter.drawPixmap(0, 0, width(), height(), background);
}

// 槽函数：处理音效开关
void GameSettingsWindow::onToggleSoundClicked()
{
    static bool soundEnabled = true;
    soundEnabled = !soundEnabled;
    emit soundToggled(soundEnabled); // 发送信号
}

// 槽函数：处理恢复默认设置
void GameSettingsWindow::onResetSettingsClicked()
{
    emit settingsReset(); // 发送信号
}

// 槽函数：处理音量改变
void GameSettingsWindow::onVolumeChanged(int level)
{
    emit volumeChanged(level); // 发送信号
}

void GameSettingsWindow::onMuteClicked()
{
    volumeSlider->setValue(0);  // 将音量滑块值设置为0
    // 其他静音处理逻辑（如设置全局音量为0）
}

