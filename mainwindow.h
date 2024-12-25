#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QVBoxLayout>

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
    void onLevelSelected(int level);  // 处理选择关卡的信号
    void onSettingsClicked();

private:
    void startGame(int level);  // 根据关卡开始游戏

};

#endif // MAINWINDOW_H
