#include "game.h"

Game::Game(int level): level(level) {
    initializeBoard();
    initializeGoalSteps();
}

//初始化棋盘√
void Game::initializeBoard(){
    int rows,cols;
    switch(level){
    case 1:
        rows = 8;
        cols = 8;
        break;
    case 2:
        rows = 10;
        cols = 10;
        break;
    }
    board = Board(rows,cols);
}

//初始化过关条件√
void Game::initializeGoalSteps(){
    switch(level){
    case 1:
        goal = 100;
        steps = 20;
        break;
    case 2:
        goal = 500;
        steps = 20;
        break;
    defalt:
        goal = 1000;
        steps = 15;
        break;
    }
}

//检测棋盘上可消除宝石√
void Game::findRemovableBlocks() {
    // 获取可消除方块的坐标列表
    std::vector<std::pair<int, int>> removableBlocks;
    board.findRemovableBlocks(removableBlocks);

    // 如果有可消除的方块
    if (!removableBlocks.empty()) {
        // 对于每个可消除的方块，执行消除操作
        for (const auto& block : removableBlocks) {
            int row = block.first;
            int col = block.second;
            // 执行消除方块的逻辑
            board.eliminateBlock(row, col);
        }

        // 消除后可以进行积分、更新步骤等操作
        changePoints(100); // 比如每消除一次，得 100 分
    }
}

//消除宝石积分√
void Game::changePoints(int increment){
    points += increment;
}

//改变游戏状态√
void Game::changeStatus(int flag){
    status = flag;
}

//步数减一√
void Game::changeSteps(){
    steps--;
}

//判断游戏是否结束√
int Game::isGameOver(){
    if(this->steps==0&&this->points < this->goal){
        return -1;
    }else if(this->points >= this->goal){
        return 1;
    }
    return 0;

}
