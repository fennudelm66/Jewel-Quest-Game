#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QVBoxLayout>
#include <QSoundEffect>
#include "audiomanager.h"  // 引入音频管理类
#include "GameSettingsWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onExitClicked();
    void onStartClicked();
    void onStageModeSelected();
    void onEndlessModeSelected();
    void onRankingClicked();
    void onSettingClicked();
    void onLevelSelected(int level);  // 处理选择关卡的信号
public:
    AudioManager *audioManager ;
private:
    void startGame(int level);  // 根据关卡开始游戏
    bool soundEnabled;                   // 是否启用声音
    int currentVolume;                   // 当前音量


};

#endif // MAINWINDOW_H
