#ifndef LEVELGAME_H
#define LEVELGAME_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include"game.h"

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
    Game game;
    QPushButton *backButton;
    void generateBlocks();
    void onAddButtonClicked();
    void onChangeButtonClicked();
    void onBlockClicked(int row, int col);

};

#endif // LEVELGAME_H
