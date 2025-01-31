#include "EndlessModeWindow.h"
#include"mainwindow.h"
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
    timeLeft(5),  // 初始化为5分钟（300秒
    game(this, 1)
{
    game.board->setGeometry(0,0,800,800);

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

    // 创建并设置返回按钮
    QPushButton *backButton;
    backButton = new QPushButton("返回", this);
    backButton->setGeometry(15, 50, 100, 40);  // 设置按钮的位置和大小
    backButton->setStyleSheet("background-color: yellow; color: brown; font: bold 16px;");
    connect(backButton, &QPushButton::clicked, this, &EndlessModeWindow::onBackButtonClicked);

    // 创建设置按钮并设置图标
    addButton = new QPushButton(this);
    QIcon addIcon(":/add.png");  // 设置按钮图标
    addButton->setIcon(addIcon);
    addButton->setIconSize(QSize(100, 100));  // 设置图标大小
    addButton->setFixedSize(100,100);
    addButton->setFlat(true);  // 去除按钮的边框和背景
    addButton->move(130,650);
    // 设置悬停时显示的提示文本
    addButton->setToolTip("增加时间");
    connect(addButton,&QPushButton::clicked,this,&EndlessModeWindow::onAddButtonClicked);

    // 创建设置按钮并设置图标
    changeButton = new QPushButton(this);
    QIcon changeIcon(":/change.png");  // 设置按钮图标
    changeButton->setIcon(changeIcon);
    changeButton->setIconSize(QSize(100, 100));  // 设置图标大小
    changeButton->setFixedSize(100,100);
    changeButton->setFlat(true);  // 去除按钮的边框和背景
    changeButton->move(230,650);
    changeButton->setToolTip("打乱宝石");
    connect(changeButton,&QPushButton::clicked,this,&EndlessModeWindow::onChangeButtonClicked);

    tipButton=new QPushButton(this);
    QIcon tipIcon(":/tip.bng");
    addButton->setIcon(tipIcon);
    tipButton->setIconSize(QSize(100, 100));  // 设置图标大小
    tipButton->setFixedSize(100,100);
    tipButton->setFlat(true);
    tipButton->move(30,650);
    tipButton->setToolTip("提示");
    connect(tipButton,&QPushButton::clicked,this,&EndlessModeWindow::onTipButtonClicked);

    revButton=new QPushButton(this);
    QIcon revIcon(":/rev.bng");
    addButton->setIcon(revIcon);
    revButton->setIconSize(QSize(100, 100));  // 设置图标大小
    revButton->setFixedSize(100,100);
    revButton->setFlat(true);
    revButton->move(360,650);
    revButton->setToolTip("撤回");
    connect(revButton,&QPushButton::clicked,this,&EndlessModeWindow::onRevButtonClicked);


    // 创建一个背景框 (QFrame)
    QFrame *backgroundFrame = new QFrame(this);
    backgroundFrame->setGeometry(50, 130, 370, 370);  // 设置背景框的大小和位置
    // 设置背景框的样式为黑色半透明
    backgroundFrame->setStyleSheet("background-color: rgba(0, 0, 0, 0.5)");

    // 让背景框不拦截鼠标事件，确保按键可以被点击
    backgroundFrame->setAttribute(Qt::WA_TransparentForMouseEvents);
    backgroundFrame->lower();

    pointLabel=new QLabel(this);
    pointLabel->setStyleSheet("font-weight: bold; font-size: 40px; color: white;");
    pointLabel->setGeometry(30,550,300,50);
    pointLabel->setText("分数："+QString::number(game.points));

    generateBlocks();
}


EndlessModeWindow::~EndlessModeWindow()
{
    delete countdownTimer;
    delete opacityAnimation;
    delete opacityEffect;
    delete countdownLabel;
    delete imageLabel;

}

void EndlessModeWindow::generateBlocks(){
    // 定义每个Block的大小和间距
    int blockWidth = 40;
    int blockHeight = 40;
    int horizontalSpacing = 5;
    int verticalSpacing = 5;

    // 定义第一个Block的位置
    int startX = 60;
    int startY = 140;

    // 创建8x8的Block，并手动计算位置
    for (int i = 0; i < game.board->getRowCount(); ++i) {
        for (int j = 0; j < game.board->getColCount(); ++j) {
            // 计算每个Block的坐标
            int xPos = startX + j * (blockWidth + horizontalSpacing);
            int yPos = startY + i * (blockHeight + verticalSpacing);
            if(game.board->getBlock(i,j) == nullptr)
                qDebug() << "Failed to load block: " ;
            // 设置Block的大小和位置
            game.board->getBlock(i,j)->setGeometry(xPos, yPos, blockWidth, blockHeight);
            connect(game.board->getBlock(i,j), &QPushButton::clicked, [this, i, j]() {
                onBlockClicked(i, j);
            });
        }
    }
}

void EndlessModeWindow::onBlockClicked(int row,int col)
{
    // 如果 block1 为空，则设置为点击的方块
    if (game.board->block1 == nullptr) {
        game.board->block1 = game.board->setChosenBlock(row, col);
        qDebug()<<"选择1成功";
    }
    // 如果 block1 不为空，且 block2 为空，则设置为点击的方块
    else if (game.board->block2 == nullptr) {
        game.board->block2 = game.board->setChosenBlock(row, col);
        qDebug()<<"选择2成功";
    }

    // 如果 block2 已经选择，检查交换是否有效
    if (game.board->block1 != nullptr && game.board->block2 != nullptr) {
        if (game.board->isActionValid()) {
            // 如果交换有效，查找可消除的方块
            game.findRemovableBlocks();
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
    messageBox->setModal(true);  // 使弹窗为非模态
    messageBox->show();

}

void EndlessModeWindow::onBackButtonClicked()
{
    // 隐藏当前 LevelGame 窗口
    this->hide();

    // 显示 MainWindow 窗口
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();

}

void EndlessModeWindow::onAddButtonClicked()
{
    timeLeft+=10;
    game.points-=100;
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

void EndlessModeWindow::onStartButtonClicked()
{
    // 启动倒计时
    countdownTimer->start();
}

void EndlessModeWindow::onChangeButtonClicked()
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
    game.board->repaint();

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

void EndlessModeWindow::onTipButtonClicked()
{

}

void EndlessModeWindow::onRevButtonClicked()
{

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
        // 显示“时间到！”的图片和文字动画

        // 弹出无尽模式结束窗口
        GameEndWindow *endWindow = new GameEndWindow(GameEndWindow::EndlessMode, game.points,game.goal, this);
        // 连接信号到槽函数
        connect(endWindow, &GameEndWindow::endWindowClosed, this, &EndlessModeWindow::closeEndlessModeWindow);
        endWindow->exec();
    }
}

void EndlessModeWindow::closeEndlessModeWindow()
{
    // 关闭无尽模式窗口
    this->close();

    // 显示 MainWindow 窗口
    MainWindow *mainWindow = new MainWindow();
    mainWindow->audioManager->stopBackgroundMusic();
    mainWindow->show();

}


