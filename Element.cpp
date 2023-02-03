#include "Element.h"

Element::Element(int x, int y, Block::BlockID id, Drawboard *drawboard) {
    this->x = x;
    this->y = y;

    this->id = id;
    this->color = Block::BlockInfo::blockColor[this->id];

    this->drawboard = drawboard;
    this->boardRows = this->drawboard->rows;
    this->boardCols = this->drawboard->cols;
}