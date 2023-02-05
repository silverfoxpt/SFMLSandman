#ifndef H_BLOCKCREATE
#define H_BLOCKCREATE

#include "Sand.h"

class BlockCreator {
    public:
        static std::shared_ptr<Element> CreateElement(int x, int y, Block::BlockID id, Drawboard* board);
};

#endif

