#include "MovableSolid.h"

void MovableSolid::step() {
    int x = this->x, y = this->y;
    if (this->drawboard->isLastRow(x)) {
        return;
    }
    std::shared_ptr<Element> curr = this->drawboard->getElement(x, y); //to me
    
    //check down
    std::shared_ptr<Element> down = this->drawboard->getElement(x-1, y); 
    if (down == nullptr) { //swap
        this->drawboard->setElement(x-1, y, curr);
        this->drawboard->setElement(x, y, down);
        return;
    }   

    //check left
    if (!this->drawboard->isFirstCol(y)) {
        std::shared_ptr<Element> left = this->drawboard->getElement(x-1, y-1);
        if (left == nullptr) { //swap
            this->drawboard->setElement(x-1, y-1, curr);
            this->drawboard->setElement(x, y, left);
            return;
        }
    }

    //check right
    if (!this->drawboard->isLastCol(y)) {
        std::shared_ptr<Element> right = this->drawboard->getElement(x-1, y+1);
        if (right == nullptr) { //swap
            this->drawboard->setElement(x-1, y+1, curr);
            this->drawboard->setElement(x, y, right);
            return;
        }
    }
}