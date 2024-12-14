#ifndef BOARD_H
#define BOARD_H

#include "block.h"
#include <cstddef>
#include <vector>

class Board
{
public:
    Board(int rows, int cols);

    void setBlock(int row, int col, const Block& block);
    Block getBlock(int row, int col);
    int getRowCount() const;
    int getColCount() const;
    void findRemovableBlocks(std::vector<std::pair<int, int>>& removableBlocks);
//从上方生成宝石
    void generateBlock();
    void eliminateBlock(int row, int col);
//玩家选择的宝石交换
    void moveBlock();
// //宝石掉落
//     void dropBlock();
//检验操作有效性
    bool isActionValid();


private:
    std::vector<std::vector<Block>> grid;
    int rows, cols;
    Block block1 = Block(NULL, NULL);
    Block block2 = Block(NULL, NULL);
};

#endif // BOARD_H
