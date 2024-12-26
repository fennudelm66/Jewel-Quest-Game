#ifndef BOARD_H
#define BOARD_H

#include "block.h"
#include "qabstractanimation.h"
#include "qpropertyanimation.h"
#include <cstdlib>
#include <vector>

class Board : public QWidget {
public:
    QWidget *parent;

    Board(QWidget *parent, int rows, int cols);
    void initBoard();
    // 设置棋盘上的方块
    void setBlock(int row, int col, Block* block);

    //用户选择方块
    Block* setChosenBlock(int row, int col);

    // 获取棋盘上的方块
    Block* getBlock(int row, int col);

    // 获取行数和列数
    int getRowCount() const;
    int getColCount() const;

    // 查找可消除的方块
    void findRemovableBlocks(std::vector<std::pair<int, int>>& removableBlocks);

    //动画
    QPropertyAnimation *setAnimation(Block*, int sx, int sy, int ex, int ey);

    // 从上方生成新方块
    void generateBlock();

    void refreshGrid ();

    // 消除并填充方块
    void eliminateBlock(int row, int col);

    // 交换方块
    void moveBlock();

    // 检查是否可以交换方块
    bool isActionValid();
    Block* block1 = nullptr;  // 选择的第一个方块
    Block* block2 = nullptr;  // 选择的第二个方块


private:
    std::vector<std::vector<Block*>> grid;  // 存储 Block 指针
    int rows, cols;

    // 定义每个 Block 的大小和间距
    int blockWidth = 40;
    int blockHeight = 40;
    int horizontalSpacing = 5;
    int verticalSpacing = 5;

    // 定义网格中心 Block 的位置（例如：我们希望中心位置为 centerX, centerY）
    int centerX = 250; // 设置中心 X 坐标
    int centerY = 330; // 设置中心 Y 坐标

    // 计算网格的总宽度和总高度
    int totalWidth = this->getRowCount() * (blockWidth + horizontalSpacing) - horizontalSpacing;  // 网格的总宽度
    int totalHeight = this->getColCount() * (blockHeight + verticalSpacing) - verticalSpacing;   // 网格的总高度

    // 计算起始位置，使得整个网格居中
    int startX = centerX - totalWidth / 2;  // 左上角的 x 坐标
    int startY = centerY - totalHeight / 2; // 左上角的 y 坐标

};

#endif // BOARD_H
