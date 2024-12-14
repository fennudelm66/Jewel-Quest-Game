#include "board.h"
#include <cstdlib>

Board::Board(int rows, int cols) {
    grid.resize(rows,std::vector<Block>(cols));
}

void Board::setBlock(int row, int col, const Block& block){
    grid[row][col] = block;
}

//获取棋子√
Block Board::getBlock(int row, int col){
    if (row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size()) {
        return grid[row][col];
    }
    return Block(row, col);  // 返回默认构造的Block
}

//获取行数和列数√
int Board::getRowCount() const{
    return grid.size();
}

int Board::getColCount() const{
    return grid.empty() ? 0 : grid[0].size();
}

//扫描棋盘，找到可消除的宝石√
void Board::findRemovableBlocks(std::vector<std::pair<int, int>>& removableBlocks) {
    int rows = getRowCount();
    int cols = getColCount();

    // 用一个布尔值数组来标记哪些方块是可消除的
    std::vector<std::vector<bool>> removable(rows, std::vector<bool>(cols, false));

    // 检查横向（从左到右）
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols - 2; ++col) {
            Block& block = grid[row][col];
            if (block.getType() != NULL && block.getType() == grid[row][col + 1].getType() && block.getType() == grid[row][col + 2].getType()) {
                removable[row][col] = removable[row][col + 1] = removable[row][col + 2] = true;
            }
        }
    }

    // 检查纵向（从上到下）
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows - 2; ++row) {
            Block& block = grid[row][col];
            if (block.getType() != NULL && block.getType() == grid[row + 1][col].getType() && block.getType() == grid[row + 2][col].getType()) {
                removable[row][col] = removable[row + 1][col] = removable[row + 2][col] = true;
            }
        }
    }

    // 将所有标记为可消除的方块的坐标加入到removableBlocks列表中
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (removable[row][col]) {
                removableBlocks.push_back({row, col});
            }
        }
    }
}

//从上方随机生成方块√
void Board::generateBlock() {
    // 遍历每一列，检查最上方的空位并生成新的方块
    for (int col = 0; col < cols; ++col) {
        // 找到这一列最上方的空位置
        bool foundEmpty = false;
        for (int row = 0; row < rows; ++row) {
            if (grid[row][col].getType() == 0) {  // 找到空位
                // 在这个空位上生成一个新的随机方块
                grid[row][col] = Block(rand() % 3 + 1, rand() % 3 + 1);  // 生成一个新的方块
                foundEmpty = true;
                break;
            }
        }
    }
}

//消除并填充方块√
void Board::eliminateBlock(int row, int col) {
    // 让该位置的方块被清空或设置为默认状态
    grid[row][col] = Block(NULL, NULL);  // 或者设置为空块

    // 让上方的方块掉落
    for (int r = row - 1; r >= 0; --r) {
        grid[r + 1][col] = grid[r][col];  // 将上方的方块下移
    }

    // 最顶行填充新的方块
    generateBlock();  // 假设这里是新的空方块或随机生成的方块
}

//交换选择的方块√
void Board::moveBlock(){
    // 获取 block1 和 block2 的位置
    int row1 = block1.getX();
    int col1 = block1.getY();
    int row2 = block2.getX();
    int col2 = block2.getY();
    // 交换 grid 中这两个位置的方块
    Block temp = grid[row1][col1];
    grid[row1][col1] = grid[row2][col2];
    grid[row2][col2] = temp;

    // 更新 block1 和 block2 的位置
    block1.setPosition(NULL, NULL);
    block2.setPosition(NULL, NULL);
}

// void Board::dropBlock(){}

//检验选择的两个方块是否能够交换√
bool Board::isActionValid() {
    int row1 = block1.getX();
    int col1 = block1.getY();
    int row2 = block2.getX();
    int col2 = block2.getY();

    // 检查两者是否在棋盘范围内
    if (row1 < 0 || row1 >= rows || col1 < 0 || col1 >= cols ||
        row2 < 0 || row2 >= rows || col2 < 0 || col2 >= cols) {
        return false;
    }

    // 检查 block1 和 block2 是否相邻
    if ((abs(row1 - row2) == 1 && col1 == col2) || (abs(col1 - col2) == 1 && row1 == row2)) {
        return true; // 相邻
    }

    return false;
}
