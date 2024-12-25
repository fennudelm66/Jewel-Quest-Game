#ifndef BOARD_H
#define BOARD_H

#include "block.h"
#include <cstdlib>
#include <vector>

class Board : public QWidget {
public:
    QWidget *parent;

    Board(QWidget *parent, int rows, int cols);

    // 设置棋盘上的方块
    void setBlock(int row, int col, Block* block);

    //用户选择方块
    Block setChosenBlock(int row, int col);

    // 获取棋盘上的方块
    Block* getBlock(int row, int col);

    // 获取行数和列数
    int getRowCount() const;
    int getColCount() const;

    // 查找可消除的方块
    void findRemovableBlocks(std::vector<std::pair<int, int>>& removableBlocks);

    // 从上方生成新方块
    void generateBlock();

    void refreshGrid ();

    // 消除并填充方块
    void eliminateBlock(int row, int col);

    // 交换方块
    void moveBlock();

    // 检查是否可以交换方块
    bool isActionValid();


private:

    std::vector<std::vector<Block*>> grid;  // 存储 Block 指针
    int rows, cols;
    Block* block1;  // 选择的第一个方块
    Block* block2;  // 选择的第二个方块
};

#endif // BOARD_H
