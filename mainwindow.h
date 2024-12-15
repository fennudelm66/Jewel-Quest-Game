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

};

#endif // MAINWINDOW_H
