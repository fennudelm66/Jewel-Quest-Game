#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game : public QWidget {
    Q_OBJECT
public:
    Game(QWidget *parent, int level);
    Board *board;
//消除方块
    void findRemovableBlocks();
    void changePoints(int increment);

//控制玩家是否可操作
    void changeStatus(int flag);

    void changeSteps();

//检验游戏是否结束
    int isGameOver();

    struct GameState {
        int points;        // 当前得分
        int steps;         // 当前步数
        int status;        // 当前玩家状态
        std::vector<std::vector<Block*>> grid;;

        // 可以添加更多字段来记录棋盘状态，具体字段取决于 Board 类
    };
    // 记录当前状态
    void recordState();

    void limitHistorySize();

    // 获取历史记录
    std::vector<GameState> getHistory() const { return history; }

    //撤销步骤
    void revertToLastState() ;

private:
    int level;
    int points = 0;
    int status;
    int goal;
    int steps;

    // 游戏状态历史记录
    std::vector<GameState> history;

//初始化棋盘和关卡条件
    void initializeBoard();
    void initializeGoalSteps();
};


#endif // GAME_H
