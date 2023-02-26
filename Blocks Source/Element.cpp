#include "../Blocks Header/Element.h"

Element::Element(int x, int y, Block::BlockID id, Drawboard *drawboard) {
    this->x = x;
    this->y = y;
    this->isFreeFalling = true;         //always falling first
    this->xThreshold = 0.0;
    this->yThreshold = 0.0;

    this->frictionFactor = 1.0;         //default
    this->inertialResistance = 0.0;     //default

    this->id = id;
    this->color = Block::BlockInfo::randomPickColor(this->id);

    this->drawboard = drawboard;
    this->boardRows = this->drawboard->rows;
    this->boardCols = this->drawboard->cols;
}

int Element::getPhysicX() {
    return this->y + 1;
}

int Element::getPhysicY() {
    return this->drawboard->rows - this->x; 
}

void Element::setElementToFreeFalling() {
    if (this->isFreeFalling == true) {return;}
    this->isFreeFalling = (Random::getRandomFloat() > this->inertialResistance) ? true : false;
}

bool Element::actOnNeighbor(std::shared_ptr<Element> neighbor, int neighborPhysX, int neighborPhysY, bool isFinal, bool isFirst, int depth, sf::Vector2i lastLocation) {
    return true;
}

void Element::setAdjacentNeighborFreeFalling(sf::Vector2i lastValidLocation, int depth) {
    return;
}