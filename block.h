#ifndef BLOCK_H
#define BLOCK_H

class Block
{
public:
    Block();
    Block(int x, int y);

    int getX() const;
    int getY() const;
    int getType() const;
    void setType(int newType);
    void setPosition(int newX, int newY);

private:
    // //用于区分被选中的棋子
    // int status;

    //不同类型宝石、道具
    int type;
    int x,y;

};

#endif // BLOCK_H
