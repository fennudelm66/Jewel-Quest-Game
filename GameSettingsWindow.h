#ifndef GAMESETTINGSWINDOW_H
#define GAMESETTINGSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include "audiomanager.h"  // 引入 AudioManager

class GameSettingsWindow : public QWidget
{
    Q_OBJECT

public:
    GameSettingsWindow(QWidget *parent = nullptr, AudioManager *audioMgr = nullptr);  // 构造函数

private slots:
    void toggleSound();    // 音效开关
    void resetSettings();  // 恢复默认设置
    void updateVolume(int volume);  // 更新音量
    void closeWindow();  // 关闭窗口的槽

protected:
    void paintEvent(QPaintEvent *event) override;  // 绘制背景图片

private:
    AudioManager *audioManager;  // AudioManager 实例
    QPushButton *closeButton;  // 关闭按钮
    bool soundEnabled;           // 音效开关
    int currentVolume;           // 当前音量
};

#endif // GAMESETTINGSWINDOW_H
