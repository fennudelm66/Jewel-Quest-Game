#include "block.h"

Block::Block(int x, int y) :type(0) {
    this->x = x;
    this->y = y;
}

//获取棋子坐标√
int Block::getX() const{
    return x;
}

int Block::getY() const{
    return y;
}

//改变棋子位置√
void Block::setPosition(int newX, int newY){
    x = newX;
    y = newY;
}

void Block::setType(int newType){
    this->type = newType;
}
