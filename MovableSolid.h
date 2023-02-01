#ifndef H_MOVABLESOLID
#define H_MOVABLESOLID

#include "Solid.h"

class MovableSolid : public Solid{
    public:
        MovableSolid(int x, int y, Block::BlockID id) : Solid(x, y, id) {

        }

        virtual void step() {
            
        }
};

#endif