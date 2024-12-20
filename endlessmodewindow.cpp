#include "EndlessModeWindow.h"
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QRandomGenerator>


EndlessModeWindow::EndlessModeWindow(QWidget *parent)
    : QWidget(parent),
    imageLabel(new QLabel(this)),
    countdownLabel(new QLabel(this)),
    opacityEffect(new QGraphicsOpacityEffect(this)),
    opacityAnimation(new QPropertyAnimation(opacityEffect, "opacity", this)),
    countdownTimer(new QTimer(this)),
    timeLeft(300)  // 初始化为5分钟（300秒）
{
    setWindowTitle("无限模式");

    // 设置窗口大小
    setFixedSize(500, 800);

    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 创建一个布局用于显示倒计时标签
    QVBoxLayout *topLayout = new QVBoxLayout();
    topLayout->addWidget(countdownLabel);
    topLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);  // 左上角对齐
    layout->addLayout(topLayout);

    // 设置背景图片并自适应
    QPixmap backgroundImage(":/LevelBackground.png");  // 你的背景图片路径
    QPalette palette;
    backgroundImage = backgroundImage.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 自适应
    palette.setBrush(QPalette::Window, QBrush(backgroundImage));  // 设置背景
    setPalette(palette);

    // 设置倒计时显示
    countdownLabel->setText("05:00");
    countdownLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);  // 左上角显示
    countdownLabel->setStyleSheet("QLabel { font-size: 24px; font-weight: bold; color: white; background: transparent; }");

    // 设置透明度效果
    setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(1.0);  // 初始透明度为1

    // 设置透明度动画
    opacityAnimation->setDuration(500);  // 动画持续时间：500ms
    opacityAnimation->setStartValue(0.0);  // 初始透明度
    opacityAnimation->setEndValue(1.0);    // 结束透明度

    // 启动透明度动画
    opacityAnimation->start();

    // 设置倒计时定时器
    countdownTimer->setInterval(1000);  // 每秒更新时间
    connect(countdownTimer, &QTimer::timeout, this, &EndlessModeWindow::updateCountdown);


    // 显示弹窗
    showStartDialog();

    // 定义每个Block的大小和间距
    int blockWidth = 40;
    int blockHeight = 40;
    int horizontalSpacing = 5;
    int verticalSpacing = 5;

    // 定义第一个Block的位置
    int startX = 25;
    int startY = 130;

    // 存储Block对象指针
    blocks.clear(); // 清空现有Block

    // 创建8x8的Block，并手动计算位置
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // 计算每个Block的坐标
            int xPos = startX + j * (blockWidth + horizontalSpacing);
            int yPos = startY + i * (blockHeight + verticalSpacing);

            // 创建Block，并设置随机类型
            int randomType = QRandomGenerator::global()->bounded(3); // 随机生成0, 1, 或 2
            Block *block = new Block(this, randomType, xPos, yPos);

            // 设置Block的大小和位置
            block->setGeometry(xPos, yPos, blockWidth, blockHeight);

            // 存储Block对象
            blocks.append(block);

            // 如果需要，可以在这里做其他操作（例如设置信号槽等）
        }
    }
}


EndlessModeWindow::~EndlessModeWindow()
{
    delete countdownTimer;
    delete opacityAnimation;
    delete opacityEffect;
    delete countdownLabel;
    delete imageLabel;

    // 清理动态分配的Block
    qDeleteAll(blocks);
    blocks.clear();

}

void EndlessModeWindow::showStartDialog()
{
    // 创建一个 QMessageBox 对象，但不阻塞主窗口
    QMessageBox *messageBox = new QMessageBox(this);
    messageBox->setIcon(QMessageBox::Information);
    messageBox->setWindowTitle("提示");
    messageBox->setText("请在五分钟内尽可能消除方块");
    messageBox->setStandardButtons(QMessageBox::Ok);

    // 设置背景颜色和其他样式
    messageBox->setStyleSheet("QMessageBox {"
                              "background-color: yellow;"  // 设置背景色
                              "border: 2px solid brown;"   // 边框颜色
                              "border-radius: 10px;"          // 圆角
                              "}"
                              "QLabel {"
                              "color: brown;"              // 设置文本颜色
                              "font: bold 16px;"             // 设置字体样式
                              "}"
                              "QPushButton {"
                              "background-color: #4CAF50;"   // 按钮背景色
                              "color: white;"                // 按钮文本颜色
                              "font: bold 14px;"             // 按钮字体
                              "border-radius: 5px;"          // 按钮圆角
                              "padding: 10px 20px;"          // 按钮内边距
                              "}"
                              "QPushButton:hover {"
                              "background-color: #45a049;"   // 按钮悬停时的背景色
                              "}");


    // 连接按钮的点击事件，点击后开始倒计时
    connect(messageBox, &QMessageBox::accepted, this, &EndlessModeWindow::onStartButtonClicked);

    // 设置为非模态的弹窗（允许与主窗口交互）
    messageBox->setModal(false);  // 使弹窗为非模态
    messageBox->show();


}

void EndlessModeWindow::onStartButtonClicked()
{
    // 启动倒计时
    countdownTimer->start();
}

void EndlessModeWindow::updateCountdown()
{
    if (timeLeft > 0) {
        timeLeft--;

        // 计算剩余时间并更新标签
        int minutes = timeLeft / 60;
        int seconds = timeLeft % 60;
        countdownLabel->setText(QString("%1:%2")
                                    .arg(minutes, 2, 10, QChar('0'))
                                    .arg(seconds, 2, 10, QChar('0')));
    } else {
        countdownTimer->stop();
        countdownLabel->setText("时间到！");
        // 可以在这里添加时间结束后的处理代码，比如结束游戏等。
    }
}
