#include "board.h"


Board::Board(int rows, int cols) : rows(rows), cols(cols) {
    grid.resize(rows, std::vector<Block*>(cols, nullptr));
}

void Board::setBlock(int row, int col, Block* block) {
    // 确保删除旧的 Block 对象（如果有的话）
    if (grid[row][col] != nullptr) {
        delete grid[row][col];
    }
    grid[row][col] = block;
}

Block* Board::getBlock(int row, int col) {
    return grid[row][col];
}

int Board::getRowCount() const {
    return rows;
}

int Board::getColCount() const {
    return cols;
}

void Board::findRemovableBlocks(std::vector<std::pair<int, int>>& removableBlocks) {
    int rows = getRowCount();
    int cols = getColCount();

    // 用一个布尔值数组来标记哪些方块是可消除的
    std::vector<std::vector<bool>> removable(rows, std::vector<bool>(cols, false));

    // 检查横向（从左到右）
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols - 2; ++col) {
            if (grid[row][col] != nullptr && grid[row][col]->getType() != 0 &&
                grid[row][col]->getType() == grid[row][col + 1]->getType() &&
                grid[row][col]->getType() == grid[row][col + 2]->getType()) {
                removable[row][col] = removable[row][col + 1] = removable[row][col + 2] = true;
            }
        }
    }

    // 检查纵向（从上到下）
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows - 2; ++row) {
            if (grid[row][col] != nullptr && grid[row][col]->getType() != 0 &&
                grid[row][col]->getType() == grid[row + 1][col]->getType() &&
                grid[row][col]->getType() == grid[row + 2][col]->getType()) {
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

void Board::generateBlock() {
    for (int col = 0; col < cols; ++col) {
        bool foundEmpty = false;
        for (int row = 0; row < rows; ++row) {
            if (grid[row][col] == nullptr) {  // 找到空位
                // 创建一个新的 Block 对象，并将其指针存储在 grid 中
                grid[row][col] = new Block(nullptr,rand() % 3 + 1);  // 传入随机类型（1, 2, 或 3）
                foundEmpty = true;
                break;
            }
        }
    }
}


void Board::eliminateBlock(int row, int col) {
    // 删除该位置的方块
    delete grid[row][col];
    grid[row][col] = nullptr;

    // 让上方的方块掉落
    for (int r = row - 1; r >= 0; --r) {
        grid[r + 1][col] = grid[r][col];
    }

    // 最顶行填充新的方块
    generateBlock();
}

void Board::moveBlock() {
    int row1 = block1->getY();
    int col1 = block1->getX();
    int row2 = block2->getY();
    int col2 = block2->getX();

    // 交换 grid 中这两个位置的方块
    Block* temp = grid[row1][col1];
    grid[row1][col1] = grid[row2][col2];
    grid[row2][col2] = temp;

    // 更新 block1 和 block2 的位置
    block1 = nullptr;
    block2 = nullptr;
}

bool Board::isActionValid() {
    int row1 = block1->getY();
    int col1 = block1->getX();
    int row2 = block2->getY();
    int col2 = block2->getX();

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
