#include "LevelGame.h"
#include"mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QPalette>
#include <QRandomGenerator>

LevelGame::LevelGame(int level, QWidget *parent)
    : QWidget(parent), level(level)
{
    // 设置窗口标题
    setWindowTitle("关卡模式");
    // 设置窗口大小
    setFixedSize(500, 800);

    // 设置背景图片并自适应
    QPixmap backgroundImage(":/LevelBackground.png");  // 你的背景图片路径
    QPalette palette;
    backgroundImage = backgroundImage.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 自适应
    palette.setBrush(QPalette::Window, QBrush(backgroundImage));  // 设置背景
    setPalette(palette);


    // 根据关卡生成数字
    generateNumberForLevel();
    generateBlocks(generateNumber);

    // 创建并设置返回按钮
    backButton = new QPushButton("返回", this);
    backButton->setGeometry(30, 30, 100, 40);  // 设置按钮的位置和大小
    backButton->setStyleSheet("background-color: yellow; color: brown; font: bold 16px;");
    connect(backButton, &QPushButton::clicked, this, &LevelGame::onBackButtonClicked);


    // 创建设置按钮并设置图标
    QPushButton *addButton = new QPushButton(this);
    QIcon addIcon(":/add.png");  // 设置按钮图标
    addButton->setIcon(addIcon);
    addButton->setIconSize(QSize(100, 100));  // 设置图标大小
    addButton->setFixedSize(100,100);
    addButton->setFlat(true);  // 去除按钮的边框和背景
    addButton->move(150,600);
    // 设置悬停时显示的提示文本
    addButton->setToolTip("增加步数");

    // 创建设置按钮并设置图标
    QPushButton *changeButton = new QPushButton(this);
    QIcon changeIcon(":/change.png");  // 设置按钮图标
    changeButton->setIcon(changeIcon);
    changeButton->setIconSize(QSize(100, 100));  // 设置图标大小
    changeButton->setFixedSize(100,100);
    changeButton->setFlat(true);  // 去除按钮的边框和背景
    changeButton->move(250,600);
    changeButton->setToolTip("打乱宝石");
}

LevelGame::~LevelGame()
{
}

void LevelGame::generateNumberForLevel()
{
    generateNumber=0;

    // 根据关卡数生成不同的数字
    switch (level) {
    case 1:
        generateNumber = 9;
        break;
    case 2:
        generateNumber = 8;
        break;
    case 3:
        generateNumber = 7;
        break;
    default:
        generateNumber = -1;  // 如果关卡数不在1到3之间，则返回无效数字
        break;
    }

}

void LevelGame::generateBlocks(int n) {

    // 创建一个背景框 (QFrame)
    QFrame *backgroundFrame = new QFrame(this);
    backgroundFrame->setGeometry(45, 125, 420, 420);  // 设置背景框的大小和位置
    // 设置背景框的样式为黑色半透明
    backgroundFrame->setStyleSheet("background-color: rgba(0, 0, 0, 0.5)");

    // 让背景框不拦截鼠标事件，确保按键可以被点击
    backgroundFrame->setAttribute(Qt::WA_TransparentForMouseEvents);

    // 定义每个 Block 的大小和间距
    int blockWidth = 40;
    int blockHeight = 40;
    int horizontalSpacing = 5;
    int verticalSpacing = 5;

    // 定义网格中心 Block 的位置（例如：我们希望中心位置为 centerX, centerY）
    int centerX = 250; // 设置中心 X 坐标
    int centerY = 330; // 设置中心 Y 坐标

    // 计算网格的总宽度和总高度
    int totalWidth = n * (blockWidth + horizontalSpacing) - horizontalSpacing;  // 网格的总宽度
    int totalHeight = n * (blockHeight + verticalSpacing) - verticalSpacing;   // 网格的总高度

    // 计算起始位置，使得整个网格居中
    int startX = centerX - totalWidth / 2;  // 左上角的 x 坐标
    int startY = centerY - totalHeight / 2; // 左上角的 y 坐标

    // 存储 Block 对象指针
    blocks.clear();  // 清空现有 Block

    // 创建 n * n 的 Block 网格，并手动计算位置
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // 计算每个 Block 的坐标
            int xPos = startX + j * (blockWidth + horizontalSpacing);
            int yPos = startY + i * (blockHeight + verticalSpacing);

            // 创建 Block，并设置随机类型
            int randomType = QRandomGenerator::global()->bounded(3); // 随机生成 0, 1, 或 2
            Block *block = new Block(this, randomType, xPos, yPos);  // 将 Block 加入到背景中

            // 设置 Block 的大小和位置
            block->setGeometry(xPos, yPos, blockWidth, blockHeight);

            // 存储 Block 对象
            blocks.append(block);
        }
    }

}


void LevelGame::onBackButtonClicked()
{
    // 隐藏当前 LevelGame 窗口
    this->hide();

    // 显示 MainWindow 窗口
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}
