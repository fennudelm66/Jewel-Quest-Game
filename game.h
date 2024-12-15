#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game
{
public:
    Game(int level);
//消除方块
    void findRemovableBlocks();
    void changePoints(int increment);

//控制玩家是否可操作
    void changeStatus(int flag);

    void changeSteps();

//检验游戏是否结束
    int isGameOver();

private:
    int level;
    int points = 0;
    int status;
    int goal;
    int steps;
    Board board = Board(0, 0);
//初始化棋盘和关卡条件
    void initializeBoard();
    void initializeGoalSteps();
};


#endif // GAME_H
