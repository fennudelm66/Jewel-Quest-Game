#ifndef GAMESETTINGSWINDOW_H
#define GAMESETTINGSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

class GameSettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameSettingsWindow(QWidget *parent = nullptr); // 构造函数

protected:
    void paintEvent(QPaintEvent *event) override; // 绘制背景事件

signals:
    void soundToggled(bool enabled);  // 信号：音效开关状态变化
    void settingsReset();             // 信号：恢复默认设置
    void volumeChanged(int level);    // 信号：音量改变

private slots:
    void onToggleSoundClicked();
    void onResetSettingsClicked();
    void onVolumeChanged(int level);
    void onMuteClicked();

private:
    QPushButton *toggleSoundButton;  // 音效开关按钮
    QPushButton *resetSettingsButton; // 恢复默认按钮
    QPushButton *closeButton;         // 关闭按钮
    QSlider *volumeSlider;            // 音量滑块
    QLabel *volumeLabel;              // 音量标签
};

#endif // GAMESETTINGSWINDOW_H
