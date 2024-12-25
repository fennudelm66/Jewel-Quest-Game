#ifndef LEVELGAME_H
#define LEVELGAME_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include"block.h"

class LevelGame : public QWidget
{
    Q_OBJECT

public:
    explicit LevelGame(int level, QWidget *parent = nullptr);
    ~LevelGame();

private slots:
    void onBackButtonClicked();  // 返回按钮点击事件

private:
    int level;
    int generateNumber;
    QVector<Block*> blocks;
    QPushButton *backButton;
    void generateNumberForLevel();
    void generateBlocks(int n);

};

#endif // LEVELGAME_H
