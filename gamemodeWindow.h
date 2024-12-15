#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>

class GameModeWindow : public QWidget
{
    Q_OBJECT

public:
    GameModeWindow(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setFixedSize(400, 300);  // 设置窗口大小

        // 设置背景图
        setAutoFillBackground(true);

        // 设置窗口属性为透明背景
        setAttribute(Qt::WA_TranslucentBackground);


        // 创建 "闯关模式" 按钮
        QPushButton *stageModeButton = new QPushButton("闯关模式", this);
        stageModeButton->setStyleSheet("background-color: yellow; color: brown; font: bold 16px;");
        stageModeButton->setFixedSize(120, 60);
        stageModeButton->move(140, 120);  // 设置位置

        // 创建 "无尽模式" 按钮
        QPushButton *endlessModeButton = new QPushButton("无尽模式", this);
        endlessModeButton->setStyleSheet("background-color: yellow; color: brown; font: bold 16px;");
        endlessModeButton->setFixedSize(120, 60);
        endlessModeButton->move(140, 190);  // 设置位置

        // 创建关闭按钮
        QPushButton *closeButton = new QPushButton("×", this);
        closeButton->setStyleSheet("background-color: transparent; color: white; font: bold 20px;");
        closeButton->setFixedSize(30, 30);
        closeButton->move(350, 80);  // 设置关闭按钮的位置（右上角）


        // 连接按钮的点击事件
        connect(stageModeButton, &QPushButton::clicked, this, &GameModeWindow::onStageModeClicked);
        connect(endlessModeButton, &QPushButton::clicked, this, &GameModeWindow::onEndlessModeClicked);
         connect(closeButton, &QPushButton::clicked, this, &GameModeWindow::close);  // 连接关闭按钮的点击事件
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        QPixmap background(":/PopupBackground.png");  // 加载背景图片

        // 设置透明背景
        painter.setOpacity(1.0);  // 设置完全不透明的背景图
        painter.drawPixmap(0, 0, width(), height(), background);  // 让背景图适应整个窗口大小
    }

signals:
    void stageModeSelected();
    void endlessModeSelected();

private slots:
    void onStageModeClicked()
    {
        // 处理闯关模式逻辑
        emit stageModeSelected();
        close();  // 关闭当前窗口
    }

    void onEndlessModeClicked()
    {
        // 处理无尽模式逻辑
        emit endlessModeSelected();
        close();  // 关闭当前窗口
    }

};
