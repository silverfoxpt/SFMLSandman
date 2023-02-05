#include "MovableSolid.h"

void MovableSolid::step()  {
    int x = this->x, y = this->y;
    if (this->drawboard->isLastRow(x)) {
        return;
    }
    
    //check down
    std::shared_ptr<Element> down = this->drawboard->getElement(x+1, y); 
    if (down == nullptr) { //swap
        this->drawboard->Swap(x, y, x+1, y);
        return;
    }   

    //check left
    if (!this->drawboard->isFirstCol(y)) {
        std::shared_ptr<Element> left = this->drawboard->getElement(x+1, y-1);
        if (left == nullptr) { //swap
            this->drawboard->Swap(x, y, x+1, y-1);
            return;
        }
    }

    //check right
    if (!this->drawboard->isLastCol(y)) {
        std::shared_ptr<Element> right = this->drawboard->getElement(x+1, y+1);
        if (right == nullptr) { //swap
            this->drawboard->Swap(x, y, x+1, y+1);
            return;
        }
    }
} 