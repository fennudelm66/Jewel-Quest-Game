#include "LevelGame.h"
#include"mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QPalette>
#include <QRandomGenerator>

LevelGame::LevelGame(int level, QWidget *parent)
    : QWidget(parent), level(level),game(this,level)
{
    // 设置窗口标题
    setWindowTitle("关卡模式");
    // 设置窗口大小
    setFixedSize(500, 800);

    game.board->setGeometry(0,0,800,800);

    // 设置背景图片并自适应
    QPixmap backgroundImage(":/LevelBackground.png");  // 你的背景图片路径
    QPalette palette;
    backgroundImage = backgroundImage.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 自适应
    palette.setBrush(QPalette::Window, QBrush(backgroundImage));  // 设置背景
    setPalette(palette);


    // 根据关卡生成数字
    generateBlocks();

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
    connect(addButton,&QPushButton::clicked,this,&LevelGame::onAddButtonClicked);

    // 创建设置按钮并设置图标
    QPushButton *changeButton = new QPushButton(this);
    QIcon changeIcon(":/change.png");  // 设置按钮图标
    changeButton->setIcon(changeIcon);
    changeButton->setIconSize(QSize(100, 100));  // 设置图标大小
    changeButton->setFixedSize(100,100);
    changeButton->setFlat(true);  // 去除按钮的边框和背景
    changeButton->move(250,600);
    changeButton->setToolTip("打乱宝石");
    connect(changeButton,&QPushButton::clicked,this,&LevelGame::onChangeButtonClicked);


    // 创建一个背景框 (QFrame)
    QFrame *backgroundFrame = new QFrame(this);
    backgroundFrame->setGeometry(45, 125, 420, 420);  // 设置背景框的大小和位置
    // 设置背景框的样式为黑色半透明
    backgroundFrame->setStyleSheet("background-color: rgba(0, 0, 0, 0.5)");

    // 让背景框不拦截鼠标事件，确保按键可以被点击
    backgroundFrame->setAttribute(Qt::WA_TransparentForMouseEvents);

    backgroundFrame->lower();


}

LevelGame::~LevelGame()
{
}

void LevelGame::generateBlocks() {

    for (int i = 0; i < game.board->getRowCount(); ++i) {
        for (int j = 0; j < game.board->getColCount(); ++j) {

            // 连接信号与槽函数
            connect(game.board->getBlock(i,j), &QPushButton::clicked, [this, i, j]() {
                onBlockClicked(i, j);
            });
        }
    }
}

void LevelGame::onAddButtonClicked()
{

}

void LevelGame::onChangeButtonClicked()
{
    game.board->refreshGrid();
    generateBlocks();
    game.board->repaint();
}


void LevelGame::onBackButtonClicked()
{
    // 隐藏当前 LevelGame 窗口
    this->hide();

    // 显示 MainWindow 窗口
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}

void LevelGame::onBlockClicked(int row, int col)
{
    // 如果 block1 为空，则设置为点击的方块
    if (game.board->block1 == nullptr) {
        game.board->block1 = game.board->setChosenBlock(row, col);
        // 设置按钮的背景透明度

        // 设置按钮为可切换状态
        game.board->block1->setCheckable(true);

        game.board->block1->setStyleSheet(
            "QPushButton {"
            "   background-color: lightblue;" // 普通状态下的背景颜色
            "   border: 2px solid #4CAF50;"
            "   border-radius: 8px;"
            "   padding: 10px;"
            "   font-size: 16px;"
            "}"
            "QPushButton:checked {"
            "   background-color: lightcoral;" // 被点击（选中）后的背景颜色
            "}"
            );
        qDebug()<<"选择1成功";
    }  // 如果 block1 不为空，且 block2 为空，则设置为点击的方块
    else if (game.board->block2 == nullptr) {
        game.board->block2 = game.board->setChosenBlock(row, col);
        qDebug()<<"选择2成功";
        printf("%d %d",game.board->block1->getX(),game.board->block2->getX());
    }

    // 如果 block2 已经选择，检查交换是否有效
    else {
        qDebug()<<"选择1和2成功";
        if (game.board->isActionValid()) {
            qDebug()<<"交换合法";
            // 如果交换有效，查找可消除的方块
            game.board->moveBlock();
            game.findRemovableBlocks();
        }
        else {
            qDebug()<<"交换不合法，重设block";
            // 如果交换无效，清空 block2 并重新选择新的 block2
            game.board->block2 = nullptr;
            game.board->block1 = game.board->setChosenBlock(row, col);
        }
    }
    generateBlocks();
}
