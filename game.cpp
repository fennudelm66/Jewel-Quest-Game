#include "game.h"
#include <ostream>
#include <iostream>

Game::Game(QWidget *parent, int level)
    : QWidget(parent), level(level){  // 在初始化列表中初始化 board

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
        rows = 9;
        cols = 9;
        break;
    case 3:
        rows = 10;
        cols = 10;
        break;
    }

    board = new Board(this, rows, cols);

    for (int i = 0; i < board->getRowCount(); ++i) {
        for (int j = 0; j < board->getColCount(); ++j) {
            board->getBlock(i,j)->hide();
        }
    }

    findRemovableBlocks();
    points = 0;
    qDebug() << "已创建棋盘";
}

//初始化过关条件√
void Game::initializeGoalSteps(){
    switch(level){
    case 1:
        goal = 200;
        steps = 5;
        break;
    case 2:
        goal = 2000;
        steps = 10;
        break;
    case 3:
        goal = 5000;
        steps = 15;
        break;
    defalt:
        goal = 10000;
        steps = 15;
        break;
    }
}

//检测棋盘上可消除宝石√
bool Game::findRemovableBlocks() {
    std::vector<std::pair<int, int>> removableBlocks;
    board->findRemovableBlocks(removableBlocks);
    // bool flag = false;

    // // 如果有可消除的方块
    // if (!removableBlocks.empty()) {
    //     flag = true; // 设置 flag 为 true
        while (!removableBlocks.empty()) {
            // 对于每个可消除的方块，执行消除操作
            for (const auto& block : removableBlocks) {
                int row = block.first;
                int col = block.second;
                // 执行消除方块的逻辑
                board->eliminateBlock(row, col); // 消除后可以进行积分、更新步骤等操作
                changePoints(100); // 比如每消除一次，得 100 分
            }
            board->generateBlock();
            board->repaint();
            // 清空可消除方块列表
            removableBlocks.clear();
            // 重新查找消除后的可消除方块
            board->findRemovableBlocks(removableBlocks);
        }
    // }
    // return flag; // 返回是否有可消除的方块
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

void Game::limitHistorySize() {
    if (history.size() > 10) {
        history.erase(history.begin());  // 删除最旧的记录
    }
}



void Game::recordState() {
    GameState state;
    state.points = points;
    state.steps = steps;
    state.status = status;
    // 记录当前棋盘状态
    for (int row = 0; row < board->getRowCount(); ++row) {
        for (int col = 0; col < board->getColCount(); ++col) {
            // 假设 board.grid 是一个二维数组
            state.grid[row][col] = board->getBlock(row, col);  // 你可以根据实际情况调用相应的方法
        }
    }

    history.push_back(state);  // 添加到历史记录

    // 限制历史记录最多存储10个元素
    limitHistorySize();
}

// 在 Game 类中添加此方法
void Game::revertToLastState() {
    // 检查是否有历史记录
    if (history.empty()) {
        std::cout << "没有历史记录，无法恢复状态！" << std::endl;
        return;  // 如果没有历史记录，直接返回
    }

    // 获取历史记录中的最后一个状态
    GameState lastState = history.back();

    // 恢复游戏状态
    points = lastState.points;
    steps = lastState.steps;
    status = lastState.status;
    for (int row = 0; row < board->getRowCount(); ++row) {
        for (int col = 0; col < board->getColCount(); ++col) {
            // 假设 board.grid 是一个二维数组
            board->setBlock(row, col, lastState.grid[row][col]);  // 你可以根据实际情况调用相应的方法
        }
    }

    // 删除历史记录中的最后一个状态
    history.pop_back();

    // 输出恢复后的状态（可选）
    std::cout << "游戏状态已恢复至最后一个历史记录。" << std::endl;
    std::cout << "得分: " << points << ", 步数: " << steps << ", 状态: " << status << std::endl;
}
