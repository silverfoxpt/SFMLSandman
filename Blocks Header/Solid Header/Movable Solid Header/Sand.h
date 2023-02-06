#ifndef H_SAND
#define H_SAND

#include "MovableSolid.h"

class Sand : public MovableSolid {
    public:
        Sand(int x, int y, Block::BlockID id, Drawboard *drawboard) : MovableSolid(x, y, id, drawboard) {
            
        }
};

#endif