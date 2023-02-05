#include "BlockCreator.h"

std::shared_ptr<Element> BlockCreator::CreateElement(int x, int y, Block::BlockID id, Drawboard* board) {
    std::shared_ptr<Element> ptr = nullptr;

    switch (id)
    {
        case(Block::BlockID::SAND): {
            Sand tmp(x, y, id, board);
            ptr = std::make_shared<Sand>(tmp);
            break;
        }
        
        default: {std::cout << "Error: block not found."; break;}
    }

    return ptr;
}