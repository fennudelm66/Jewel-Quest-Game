// LevelSelectWindow.h
#ifndef LEVELSELECTWINDOW_H
#define LEVELSELECTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>

class LevelSelectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LevelSelectWindow(QWidget *parent = nullptr);

signals:
    void levelSelected(int level);  // 选择关卡信号

private slots:
    void onLevelButtonClicked(int level);  // 按钮点击槽


private:
    QVBoxLayout *layout;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // LEVELSELECTWINDOW_H
