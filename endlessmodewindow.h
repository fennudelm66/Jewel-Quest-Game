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
#include"gameendwindow.h"
#include"game.h"

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
    QLabel *pointLabel;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *opacityAnimation;
    QPushButton *startButton;
    QPushButton *changeButton;
    QPushButton *addButton;
    QTimer *countdownTimer;
    QPushButton *tipButton;
    QPushButton *revButton;
    int timeLeft;  // 剩余时间（秒）
    Game game;

private slots:
    void onStartButtonClicked();
    void onChangeButtonClicked();
    void onTipButtonClicked();
    void onRevButtonClicked();

private:
    void updateCountdown();
    void showStartDialog();
    void onBackButtonClicked();
    void onAddButtonClicked();
    void generateBlocks();
    void onBlockClicked(int row,int col);
    void closeEndlessModeWindow();
};

#endif // ENDLESSMODEWINDOW_H
