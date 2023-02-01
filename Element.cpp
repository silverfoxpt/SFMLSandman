#include "Element.h"

Element::Element(int x, int y, Block::BlockID id) {
    this->x = x;
    this->y = y;

    this->id = id;
    this->color = Block::BlockInfo::blockColor[this->id];
}