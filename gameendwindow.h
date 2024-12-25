#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QPainter>
#include<QFont>

class GameEndWindow : public QDialog
{
    Q_OBJECT

public:
    enum GameMode {
        EndlessMode,
        StepMode
    };

    explicit GameEndWindow(GameMode mode, QWidget *parent = nullptr)
        : QDialog(parent)
    {
        // 设置窗口透明背景
        setAttribute(Qt::WA_TranslucentBackground);

        // 设置无边框窗口
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setFixedSize(400, 300);  // 窗口大小

        // 创建消息标签
        messageLabel = new QLabel(this);
        messageLabel->setAlignment(Qt::AlignCenter);

        QFont font("微软雅黑", 30, QFont::Bold);  // 设置为微软雅黑，大小16，粗体
        messageLabel->setFont(font);
        messageLabel->setStyleSheet("QLabel { color : white; }");  // 设置文字颜色为白色

        messageLabel->resize(400, 50);
        messageLabel->move(80, 130);

        // 创建图片标签
        imageLabel = new QLabel(this);
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->resize(120, 120);
        imageLabel->move(60, 100);

        // 创建按钮
        closeButton = new QPushButton("返回", this);
        closeButton->resize(80, 30);
        closeButton->move(160, 220);
        connect(closeButton, &QPushButton::clicked, this, &GameEndWindow::accept);

        // 根据游戏模式设置界面
        setupWindow(mode);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        QPixmap background(":/PopupBackground.png");

        // 如果图片为空，保持透明背景
        if (background.isNull()) {
            painter.fillRect(rect(), Qt::transparent);
        } else {
            painter.drawPixmap(0, 0, width(), height(), background);
        }
    }

private:
    QLabel *messageLabel;
    QLabel *imageLabel;
    QPushButton *closeButton;

    void setupWindow(GameMode mode)
    {
        if (mode == EndlessMode) {
            messageLabel->setText("时间到！");
            QPixmap pixmap(":/alarm.png");
            imageLabel->setPixmap(pixmap);
            imageLabel->setScaledContents(true); // 使图片自适应 QLabel 的大小
        } else if (mode == StepMode) {
            messageLabel->setText("步数耗尽");
            QPixmap pixmap(":/images/steps_exhausted.png");
            imageLabel->setPixmap(pixmap);
            imageLabel->setScaledContents(true); // 使图片自适应 QLabel 的大小
        }
    }
};
