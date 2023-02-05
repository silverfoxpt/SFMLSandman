#ifndef H_PEN
#define H_PEN

#include "Drawboard.h"
#include "BlockCreator.h"

class Pen {
    public:
        int size;
        Block::BlockID type;

        Pen(int size, Block::BlockID type, Drawboard *board);

        void setSize(int x);
        void setType(Block::BlockID x);

        void Draw(int posX, int posY);

    private:
        Drawboard *board;
};

#endif