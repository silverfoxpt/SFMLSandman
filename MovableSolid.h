#ifndef H_MOVABLESOLID
#define H_MOVABLESOLID

#include "Solid.h"

class MovableSolid : public Solid{
    public:
        MovableSolid(int x, int y, Block::BlockID id, Drawboard *drawboard) : Solid(x, y, id, drawboard) {
            this->checker = 988;
        }

        void step() override;
        int checker;
};

#endif