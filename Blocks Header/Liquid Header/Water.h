#ifndef H_WATER
#define H_WATER

#include "Liquid.h"

class Water : public Liquid {
    public:
        Water(int x, int y, Block::BlockID id, Drawboard *drawboard) : Liquid(x, y, id, drawboard) {
            
        }
};

#endif