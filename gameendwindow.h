#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QPainter>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include"mainwindow.h"

class GameEndWindow : public QDialog
{
    Q_OBJECT

public:
    enum GameMode {
        EndlessMode,
        StepMode
    };

    explicit GameEndWindow(GameMode mode, int points,int goal,QWidget *parent = nullptr)
        : QDialog(parent), m_points(points),m_goal(goal)
    {
        // 设置窗口透明背景
        setAttribute(Qt::WA_TranslucentBackground);

        // 设置无边框窗口
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setFixedSize(400, 300);  // 窗口大小

        // 创建消息标签
        messageLabel = new QLabel(this);
        messageLabel->setAlignment(Qt::AlignCenter);

        QFont font("微软雅黑", 20, QFont::Bold);  // 设置为微软雅黑，大小20，粗体
        messageLabel->setFont(font);
        messageLabel->setStyleSheet("QLabel { color : white; }");  // 设置文字颜色为白色
        messageLabel->resize(400, 50);
        messageLabel->move(50, 130);

        // 创建分数标签
        point = new QLabel(this);
        point->setAlignment(Qt::AlignCenter);
        point->setFont(font);
        point->setStyleSheet("QLabel { color : white; }");  // 设置文字颜色为白色
        point->resize(400, 50);
        point->move(50, 160);

        // 创建图片标签
        imageLabel = new QLabel(this);
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->resize(120, 120);
        imageLabel->move(60, 100);  // 调整图片标签的位置，使其在窗口中居中显示

        // 创建按钮
        closeButton = new QPushButton("返回", this);
        closeButton->resize(80, 30);
        closeButton->move(160, 220);
        closeButton->setStyleSheet("background-color: yellow; color: brown; font: bold 16px;");
        connect(closeButton, &QPushButton::clicked, this, [this, mode]() {
            onCloseButtonClicked(mode);
        });

        // 根据游戏模式设置界面
        setupWindow(mode);
    }

signals:
    void endWindowClosed(); // 关闭窗口时发送信号


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
    int m_points;  // 声明一个成员变量来存储 points
    int m_goal;
    QLabel *messageLabel;
    QLabel *imageLabel;
    QLabel *point;  // 用来显示得分的标签
    QPushButton *closeButton;

    void setupWindow(GameMode mode)
    {
        if (mode == EndlessMode) {
            messageLabel->setText("时间到！");
            point->setText("得分：" + QString::number(m_points));
            QPixmap pixmap(":/alarm.png");
            imageLabel->setPixmap(pixmap);
            imageLabel->setScaledContents(true); // 使图片自适应 QLabel 的大小
        } else if (mode == StepMode) {
            messageLabel->deleteLater();

            if(m_points<m_goal){
                point->deleteLater();
                imageLabel->resize(200, 130);
                imageLabel->move(100,85);
                QPixmap pixmap(":/fail.png");
                imageLabel->setPixmap(pixmap);
                imageLabel->setScaledContents(true); // 使图片自适应 QLabel 的大小
            }else{
                imageLabel->resize(350, 130);
                imageLabel->move(10,85);
                point->setText("得分：" + QString::number(m_points));
                point->move(100, 160);
                QPixmap pixmap(":/succeed.png");
                imageLabel->setPixmap(pixmap);
                imageLabel->setScaledContents(true); // 使图片自适应 QLabel 的大小
            }
        }
    }

    void onCloseButtonClicked(GameMode mode) {
        // 获取当前的分数

        int currentScore = m_points;
        if(mode==EndlessMode){
        // 打开文件读取当前最高分数
        QFile file("score.txt");
        int highScore = 0;  // 默认为 0 分

        if (file.exists()) {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString line = in.readLine();  // 假设文件中第一行存储了最高分
                file.close();

                // 解析文件中的最高分数
                if (!line.isEmpty()) {
                    QStringList parts = line.split(": ");
                    if (parts.size() == 2) {
                        bool ok;
                        highScore = parts[1].toInt(&ok);
                        if (!ok) {
                            highScore = 0;  // 如果转换失败，默认为 0 分
                        }
                    }
                }
            } else {
                QMessageBox::critical(this, "错误", "无法读取历史记录文件！");
                return;
            }
        }

        // 比较当前分数与文件中的分数
        if (currentScore > highScore) {
            // 如果当前分数更高，保存新的分数
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << "当前限时关卡最高纪录: " << currentScore << "\n";
                file.close();
            } else {
                QMessageBox::critical(this, "错误", "无法保存新的最高分数！");
                return;
            }
        }
    }

        // 发射信号，通知其他窗口
        emit endWindowClosed();
        // 关闭当前窗口
        this->close();
}

};
