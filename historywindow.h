#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
#include<QPushButton>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>


class HistoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryWindow(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setFixedSize(400, 300);  // 设置窗口大小

        // 设置背景图
        setAutoFillBackground(true);

        // 设置窗口属性为透明背景
        setAttribute(Qt::WA_TranslucentBackground);

        // 读取文件内容
        QString scoreContent = readHistoryFile();

        // 创建 QLabel 显示文件内容
        QLabel *scoreLabel = new QLabel(scoreContent, this);
        scoreLabel->setStyleSheet("font-weight: bold; font-size: 20px; color: white;");  // 设置字体样式
        scoreLabel->setWordWrap(true);  // 允许换行

        // 使用布局管理器
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(scoreLabel);
        layout->setAlignment(Qt::AlignCenter);

        setLayout(layout);

        // 创建关闭按钮
        QPushButton *closeButton = new QPushButton("×", this);
        closeButton->setStyleSheet("background-color: transparent; color: white; font: bold 20px;");
        closeButton->setFixedSize(30, 30);
        closeButton->move(350, 80);  // 设置关闭按钮的位置（右上角）
        connect(closeButton, &QPushButton::clicked, this, &HistoryWindow::close);  // 连接关闭按钮的点击事件

    }

private:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        QPixmap background(":/PopupBackground.png");  // 加载背景图片

        // 设置透明背景
        painter.setOpacity(1.0);  // 设置完全不透明的背景图
        painter.drawPixmap(0, 0, width(), height(), background);  // 让背景图适应整个窗口大小
    }


    QString readHistoryFile()
    {
        QFile file("score.txt");  // 假设文件路径
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "错误", "无法读取历史记录文件！");
            return "无法读取历史记录文件！";
        }

        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        // 如果文件为空，返回"当前无记录"
        if (content.isEmpty()) {
            return "当前无记录";
        }

        return content;
    }
};
