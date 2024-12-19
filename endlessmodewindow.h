#ifndef ENDLESSMODEWINDOW_H
#define ENDLESSMODEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include "block.h"

class EndlessModeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EndlessModeWindow(QWidget *parent = nullptr);
    ~EndlessModeWindow();

private:
    QLabel *imageLabel;
    QLabel *textLabel;
    QLabel *countdownLabel;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *opacityAnimation;
    QPushButton *startButton;
    QTimer *countdownTimer;
    int timeLeft;  // 剩余时间（秒）

    QVector<Block*> blocks;  // 存储所有Block的指针


private slots:
    void onStartButtonClicked();
    void updateCountdown();
    void showStartDialog();

};

#endif // ENDLESSMODEWINDOW_H
