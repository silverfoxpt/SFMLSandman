#ifndef H_BLOCKCREATE
#define H_BLOCKCREATE

#include "Blocks Header/Solid Header/Movable Solid Header/Sand.h"
#include "Blocks Header/Liquid Header/Liquid.h"

class BlockCreator {
    public:
        static std::shared_ptr<Element> CreateElement(int x, int y, Block::BlockID id, Drawboard* board);
};

#endif

