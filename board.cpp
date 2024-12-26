#include "board.h"
#include "qabstractanimation.h"
#include "qpropertyanimation.h"
#include <QParallelAnimationGroup>

using namespace std;

Board::Board(QWidget *parent, int rows, int cols) : QWidget(parent), rows(rows), cols(cols) {

    grid.resize(rows, std::vector<Block*>(cols, nullptr));
    qDebug() << "board初始化";
    initBoard();
}

Block* Board::setChosenBlock(int row, int col)
{
    if(row>=0 && col>=0 && row < rows && col<cols){
        if(grid[row][col]!=nullptr){
            return grid[row][col];
        }
    }else{
        qDebug() << "超出边界！";
        return grid[0][0];
    }

}

void Board::initBoard(){
    for (int i = 0; i < this->getRowCount(); ++i) {
        for (int j = 0; j < this->getColCount(); ++j) {
            // 计算每个 Block 的坐标
            /*
            int xPos = j * (blockHeight + verticalSpacing);
            int yPos = i * (blockHeight + verticalSpacing);*/
            grid[i][j] = new Block(this, rand()% 6, i, j);/*
            grid[i][j]->setGeometry(xPos, yPos, blockWidth, blockHeight);*/
        }
    }
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
QPropertyAnimation *Board::setAnimation(Block* block, int sx, int sy, int ex, int ey)
{
    // 创建动画来让方块从上方滑下来
    QPropertyAnimation* animation = new QPropertyAnimation(block, "pos");
    animation->setDuration(500);  // 动画时长 500ms
    animation->setStartValue(QPoint( sx, sy));  // 动画开始时，方块在上方
    animation->setEndValue(QPoint( ex, ey));  // 动画结束时，方块到达目标位置

    // 启动动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    return animation;
}

void Board::generateBlock()
{
    // game.findRemovableBlocks();
    int emptyBlock = 0;
    for (int col = 0; col < cols; ++col) {  // 遍历每列
        // 从下到上遍历该列的所有行，寻找空位
        emptyBlock = 0;
        for (int row = rows - 1; row >= 0; row--) {
            // 计算每个 Block 的坐标
            int xPos = col * (blockWidth + horizontalSpacing);
            int yPos = row * (blockHeight + verticalSpacing);
            if (grid[row][col] == nullptr) {  // 找到空位
                emptyBlock++;
            }
            else if(emptyBlock!=0&&grid[row][col]!=nullptr){
                grid[row + emptyBlock][col] = grid[row][col];
                grid[row + emptyBlock][col]->setPosition(row, col);
                grid[row][col] = nullptr; // 初始位置稍微偏上
                QPropertyAnimation* animation = setAnimation(grid[row+emptyBlock][col],xPos, yPos,  xPos, (row + emptyBlock) * (blockHeight + verticalSpacing));
                //grid[row+emptyBlock][col]->move((emptyBlock+row)40,col40);

                animation->start();
            }
        }
        qDebug() << emptyBlock;

        //将所有方块移到最下面后，生成方块
        for (int row = -1; row < rows; ) {
            if (emptyBlock != 0) {
                grid[row + emptyBlock][col] = new Block(this, rand()
                                                        % 6, row+emptyBlock, col);
                grid[row + emptyBlock][col]->show();
                // grid[row+emptyBlock][col]->move((emptyBlock+row)*40,col*40);
                // 创建动画来让方块从上方滑下来

                QPropertyAnimation* animation1 = setAnimation(grid[row+emptyBlock][col],col * (blockHeight + verticalSpacing), row * (blockHeight + verticalSpacing),  col * (blockHeight + verticalSpacing), (row + emptyBlock) *  (blockHeight + verticalSpacing));
                animation1->start();
                emptyBlock--;
            }else
                break;    //若没有空位，跳出循环
        }

    }
    qDebug() << "已生成方块";
}





void Board::refreshGrid() {
    // 遍历整个 grid
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {

            // 如果当前位置有 Block 对象（即非 nullptr），先释放它
            if (grid[row][col] != nullptr) {
                delete grid[row][col];  // 删除之前的 Block 对象
                grid[row][col] = nullptr;  // 将该位置设为 nullptr
            }
        }
    }
    qDebug() << "刷新棋盘";
    initBoard();
}



void Board::eliminateBlock(int row, int col) {
    // 删除该位置的方块
    delete grid[row][col];
    grid[row][col] = nullptr;

    // 让上方的方块掉落
    /*for (int r = row - 1; r >= 0; --r) {
        grid[r + 1][col] = grid[r][col];
    }*/
    qDebug() << "消除方块" << row << "," << col;

}

void Board::moveBlock() {
    int row1 = block1->getX();
    int col1 = block1->getY();
    int row2 = block2->getX();
    int col2 = block2->getY();

    qDebug() << "交换方块" << row1  << ","<< col1  << " "<< row2  << ","<< col2;
    // 交换 grid 中这两个位置的方块
    Block* temp = grid[row1][col1];
    grid[row1][col1] = grid[row2][col2];
    grid[row1][col1]->setPosition(row2,col2);

    grid[row2][col2] = temp;
    grid[row2][col2]->setPosition(temp->getX(),temp->getY());

    grid[row1][col1]->show();
    grid[row2][col2]->show();

    QPropertyAnimation *anim1 = setAnimation(grid[row1][col1],col1 * (blockHeight + verticalSpacing), row1 * (blockHeight + verticalSpacing),  col2 * (blockHeight + verticalSpacing), row2 * (blockHeight + verticalSpacing));
    QPropertyAnimation *anim2 = setAnimation(grid[row2][col2],col2 * (blockHeight + verticalSpacing), row2 * (blockHeight + verticalSpacing),  col1 * (blockHeight + verticalSpacing), row1 * (blockHeight + verticalSpacing));
    // QParallelAnimationGroup *group = new QParallelAnimationGroup;
    // group->addAnimation(anim1);
    // group->addAnimation(anim2);

    // group->start();
    anim1->start();
    anim2->start();

    // 更新 block1 和 block2 的位置
    /*
    block1->setStyleSheet(
        "QPushButton {"
        "   background-color: lightblue;"
        "   border: 2px solid #4CAF50;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "   font-size: 16px;"
        "}"
        );*/
    block1 = nullptr;
    block2 = nullptr;
}

bool Board::isActionValid() {
    int row1 = block1->getX();
    int col1 = block1->getY();
    int row2 = block2->getX();
    int col2 = block2->getY();

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
