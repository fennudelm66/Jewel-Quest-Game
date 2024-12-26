#include "LevelGame.h"
#include"mainwindow.h"
#include"gameendwindow.h"
#include <QDebug>
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QPalette>
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QEasingCurve>
#include<QGraphicsOpacityEffect>
#include <QTimer>

LevelGame::LevelGame(int level, QWidget *parent)
    : QWidget(parent), level(level),game(this,level)
{
    // 设置窗口标题
    setWindowTitle("关卡模式");
    // 设置窗口大小
    setFixedSize(500, 800);

     game.steps=1;

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
    addButton = new QPushButton(this);
    addButton->show();
    QIcon addIcon(":/add.png");  // 设置按钮图标
    addButton->setIcon(addIcon);
    addButton->setIconSize(QSize(100, 100));  // 设置图标大小
    addButton->setFixedSize(100,100);
    addButton->setFlat(true);  // 去除按钮的边框和背景
    addButton->move(130,650);
    // 设置悬停时显示的提示文本
    addButton->setToolTip("增加步数,需消耗100分数");
    connect(addButton,&QPushButton::clicked,this,&LevelGame::onAddButtonClicked);

    // 创建设置按钮并设置图标
    changeButton = new QPushButton(this);
    changeButton->show();
    QIcon changeIcon(":/change.png");  // 设置按钮图标
    changeButton->setIcon(changeIcon);
    changeButton->setIconSize(QSize(100, 100));  // 设置图标大小
    changeButton->setFixedSize(100,100);
    changeButton->setFlat(true);  // 去除按钮的边框和背景
    changeButton->move(270,650);
    changeButton->setToolTip("打乱宝石，需消耗200分数");
    connect(changeButton,&QPushButton::clicked,this,&LevelGame::onChangeButtonClicked);

    tipButton=new QPushButton(this);
    tipButton->show();
    QIcon tipIcon(":/tip.bng");
    addButton->setIcon(tipIcon);
    tipButton->setIconSize(QSize(100, 100));  // 设置图标大小
    tipButton->setFixedSize(100,100);
    tipButton->setFlat(true);
    tipButton->move(30,650);
    tipButton->setToolTip("提示");
    connect(tipButton,&QPushButton::clicked,this,&LevelGame::onTipButtonClicked);

    revButton=new QPushButton(this);
    revButton->show();
    QIcon revIcon(":/rev.bng");
    addButton->setIcon(revIcon);
    revButton->setIconSize(QSize(100, 100));  // 设置图标大小
    revButton->setFixedSize(100,100);
    revButton->setFlat(true);
    revButton->move(360,650);
    revButton->setToolTip("撤回");
    connect(revButton,&QPushButton::clicked,this,&LevelGame::onRevButtonClicked);

    // 创建一个背景框 (QFrame)
    QFrame *backgroundFrame = new QFrame(this);
    backgroundFrame->setGeometry(45, 125, game.board->getRowCount()*45, game.board->getColCount()*45);  // 设置背景框的大小和位置
    // 设置背景框的样式为黑色半透明
    backgroundFrame->setStyleSheet("background-color: rgba(0, 0, 0, 0.5)");

    // 让背景框不拦截鼠标事件，确保按键可以被点击
    backgroundFrame->setAttribute(Qt::WA_TransparentForMouseEvents);

    backgroundFrame->lower();

    // 创建 QLabel 控件来显示剩余步数
    stepsLabel = new QLabel(this);
    stepsLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);  // 设置文本右对齐，顶端对齐
    stepsLabel->setStyleSheet("font-weight: bold; font-size: 20px; color: white;");
    stepsLabel->setGeometry(250, 10, 200, 30);  // 设置 QLabel 的位置和大小
    // 更新 QLabel 显示的文本
    stepsLabel->setText("剩余步数：" + QString::number(game.steps));
    pointLabel=new QLabel(this);
    pointLabel->setStyleSheet("font-weight: bold; font-size: 40px; color: white;");
    pointLabel->setGeometry(30,550,300,50);
    pointLabel->setText("分数："+QString::number(game.points));


}

LevelGame::~LevelGame()
{
}

void LevelGame::generateBlocks() {

    game.board->generateBlock();
    qDebug() << "调用level的generateBlocks方法啦";

    qDebug() <<"检查可消除方块";

    // 定义每个 Block 的大小和间距
    int blockWidth = 40;
    int blockHeight = 40;
    int horizontalSpacing = 5;
    int verticalSpacing = 5;

    // 定义网格中心 Block 的位置（例如：我们希望中心位置为 centerX, centerY）
    int centerX = 250; // 设置中心 X 坐标
    int centerY = 330; // 设置中心 Y 坐标

    // 计算网格的总宽度和总高度
    int totalWidth = game.board->getRowCount() * (blockWidth + horizontalSpacing) - horizontalSpacing;  // 网格的总宽度
    int totalHeight = game.board->getColCount() * (blockHeight + verticalSpacing) - verticalSpacing;   // 网格的总高度

    // 计算起始位置，使得整个网格居中
    int startX = centerX - totalWidth / 2;  // 左上角的 x 坐标
    int startY = centerY - totalHeight / 2; // 左上角的 y 坐标

    game.board->setGeometry(45,125,450,450);

    // game.board->setStyleSheet("background-color: red; border: none;");

    game.board->update();

    // 创建 n * n 的 Block 网格，并手动计算位置
    for (int i = 0; i < game.board->getRowCount(); ++i) {
        for (int j = 0; j < game.board->getColCount(); ++j) {
            // 计算每个 Block 的坐标
            int xPos = j * (blockWidth + horizontalSpacing);
            int yPos = i * (blockHeight + verticalSpacing);
            if(game.board->getBlock(i,j) == nullptr)
            {    qDebug() << "Failed to load block: " ;
                // 设置Block的大小和位置
                // 连接信号与槽函数
            }else
                game.board->getBlock(i,j)->setGeometry(xPos, yPos, blockWidth, blockHeight);
                connect(game.board->getBlock(i,j), &QPushButton::clicked, [this, i, j]() {
                    onBlockClicked(i, j);
                });
            game.board->getBlock(i,j)->show();

            // bool isVisible = game.board->getBlock(i,j)->isVisible();
            // if (isVisible) {
            //     qDebug() << "按钮是可见的";
            // } else {
            //     qDebug() << "按钮是不可见的";
            // }
            // bool isHidden = game.board->getBlock(i,j)->isHidden();
            // if (isHidden) {
            //     qDebug() << "按钮被隐藏";
            // } else {
            //     qDebug() << "按钮没有被隐藏";
            // }
            // bool isParentVisible = game.board->getBlock(i,j)->parentWidget()->isVisible();
            // if (!isParentVisible) {
            //     qDebug() << "按钮的父控件不可见";
            // }



        }
    }
    qDebug() << "连接到槽啦";
}

void LevelGame::onAddButtonClicked()
{
    game.steps++;
    stepsLabel->setText("剩余步数：" + QString::number(game.steps));
    game.points-=100;
    pointLabel->setText("分数："+QString::number(game.points));
    // 设置初始位置和大小
    QRect startGeometry = QRect(40,460, pointLabel->width() * 1.2, pointLabel->height() * 1.2);
    QRect endGeometry = QRect(pointLabel->x(), pointLabel->y(), pointLabel->width() * 1.2, pointLabel->height() * 1.2);

    QPropertyAnimation* animation = new QPropertyAnimation(pointLabel, "geometry");
    animation->setDuration(500);  // 动画时长
    animation->setStartValue(startGeometry);
    animation->setEndValue(endGeometry);
    animation->setEasingCurve(QEasingCurve::OutBounce);

    // 动画结束后恢复原位置
    QObject::connect(animation, &QPropertyAnimation::finished, [=]() {
        // 恢复到原始位置
        pointLabel->setGeometry(startGeometry);
    });

    // 启动动画
    animation->start();

    // 创建动画：按钮的淡出效果
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(addButton);
    addButton->setGraphicsEffect(effect);

    // 设置按钮的透明度动画
    QPropertyAnimation *animation1 = new QPropertyAnimation(effect, "opacity");
    animation1->setDuration(500);  // 动画时长：1秒
    animation1->setStartValue(1.0); // 开始透明度：完全不透明
    animation1->setEndValue(0.0);   // 结束透明度：完全透明
    animation1->setEasingCurve(QEasingCurve::Linear); // 线性渐变效果

    // 在动画结束后，删除按钮并显示消息
    connect(animation1, &QPropertyAnimation::finished, [this]() {
        // 删除按钮
        addButton->deleteLater();

        // 创建并显示“道具使用成功”消息
        QLabel *successLabel = new QLabel("道具使用成功", this);
        successLabel->setStyleSheet("font-size: 20px; color: white;");
        successLabel->move(addButton->pos());  // 设置文本显示位置为按钮位置
        successLabel->show();

        // 可以设置消息持续一段时间后消失
        QTimer::singleShot(500, successLabel, &QLabel::deleteLater); // 2秒后删除标签
    });

    // 启动动画
    animation1->start();
}

void LevelGame::onChangeButtonClicked()
{
    game.points-=200;
    pointLabel->setText("分数："+QString::number(game.points));
    // 设置初始位置和大小
    QRect startGeometry = pointLabel->geometry();
    QRect endGeometry = QRect(pointLabel->x(), pointLabel->y(), pointLabel->width() * 1.2, pointLabel->height() * 1.2);

    QPropertyAnimation* animation = new QPropertyAnimation(pointLabel, "geometry");
    animation->setDuration(500);  // 动画时长
    animation->setStartValue(startGeometry);
    animation->setEndValue(endGeometry);
    animation->setEasingCurve(QEasingCurve::OutBounce);

    // 动画结束后恢复原位置
    QObject::connect(animation, &QPropertyAnimation::finished, [=]() {
        // 恢复到原始位置
        pointLabel->setGeometry(startGeometry);
    });
    // 启动动画
    animation->start();

    game.board->refreshGrid();

    generateBlocks();

    // 创建动画：按钮的淡出效果
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(changeButton);
    changeButton->setGraphicsEffect(effect);

    // 设置按钮的透明度动画
    QPropertyAnimation *animation1 = new QPropertyAnimation(effect, "opacity");
    animation1->setDuration(500);  // 动画时长：1秒
    animation1->setStartValue(1.0); // 开始透明度：完全不透明
    animation1->setEndValue(0.0);   // 结束透明度：完全透明
    animation1->setEasingCurve(QEasingCurve::Linear); // 线性渐变效果

    // 在动画结束后，删除按钮并显示消息
    connect(animation1, &QPropertyAnimation::finished, [this]() {
        // 删除按钮
        changeButton->deleteLater();

        // 创建并显示“道具使用成功”消息
        QLabel *successLabel = new QLabel("道具使用成功", this);
        successLabel->setStyleSheet("font-size: 20px; color: white;");
        successLabel->move(changeButton->pos());  // 设置文本显示位置为按钮位置
        successLabel->show();

        // 可以设置消息持续一段时间后消失
        QTimer::singleShot(500, successLabel, &QLabel::deleteLater); // 2秒后删除标签
    });

    // 启动动画
    animation1->start();
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
        qDebug()<<"选择1成功" << row << col;
    }
    // 如果 block1 不为空，且 block2 为空，则设置为点击的方块
    else if (game.board->block2 == nullptr) {
        game.board->block2 = game.board->setChosenBlock(row, col);
        qDebug()<<"选择2成功" << row << col;
        if (game.board->isActionValid()) {
            game.board->moveBlock();
            qDebug() << "交换有效" ;
            // 如果交换有效，查找可消除的方块
            game.findRemovableBlocks();
            game.steps--;
            stepsLabel->setText("剩余步数：" + QString::number(game.steps));
            EndGame(game.steps);
            pointLabel->setText("分数："+QString::number(game.points));

            // 设置初始位置和大小
            QRect startGeometry = pointLabel->geometry();
            QRect endGeometry = QRect(pointLabel->x(), pointLabel->y(), pointLabel->width() * 1.2, pointLabel->height() * 1.2);

            QPropertyAnimation* animation = new QPropertyAnimation(pointLabel, "geometry");
            animation->setDuration(500);  // 动画时长
            animation->setStartValue(startGeometry);
            animation->setEndValue(endGeometry);
            animation->setEasingCurve(QEasingCurve::OutBounce);
           // 动画结束后恢复原位置
            QObject::connect(animation, &QPropertyAnimation::finished, [=]() {
                // 恢复到原始位置
                pointLabel->setGeometry(startGeometry);
            });

            // 启动动画
            animation->start();
        }
        else {
            // 如果交换无效，清空 block2 并重新选择新的 block2
            game.board->block2 = nullptr;
            game.board->block1 = game.board->setChosenBlock(row, col);
            game.board->generateBlock();  // 生成新的方块
        }
    }




}

void LevelGame::onTipButtonClicked()
{

}

void LevelGame::onRevButtonClicked()
{

}

void LevelGame::EndGame(int steps)
{
    qDebug() << "已弹出窗口";
    // 如果步数为 0，表示关卡结束
    if (steps == 0) {
        // 弹出无尽模式结束窗口
        GameEndWindow *endWindow = new GameEndWindow(GameEndWindow::StepMode, game.points,game.goal, this);
        endWindow->setGeometry(100, 100, 400, 300);  // 设置窗口的初始位置和大小

        // 连接信号到槽函数
        connect(endWindow, &GameEndWindow::endWindowClosed, this, &LevelGame::closeLevelGameWindow);
        endWindow->exec();
    }

}

void LevelGame::closeLevelGameWindow(){
    // 关闭无尽模式窗口
    this->close();

    // 显示 MainWindow 窗口
    MainWindow *mainWindow = new MainWindow();
    mainWindow->audioManager->stopBackgroundMusic();
    mainWindow->show();
}
