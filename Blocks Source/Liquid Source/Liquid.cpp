#include "../../Blocks Header/Liquid Header/Liquid.h"

void Liquid::step() {
    int x = this->x;
    if (this->drawboard->isLastRow(x)) {
        return;
    }
    
    //damp x, but water
    if (this->isFreeFalling) {
        this->vel.x *= 0.8;
    }

    int xModifier = this->vel.x > 0 ? 1 : -1;
    int yModifier = this->vel.y > 0 ? 1 : -1;

    float xVal = Math::abs(vel.x) * Block::BlockInfo::frameUpdateRate;
    float yVal = Math::abs(vel.y) * Block::BlockInfo::frameUpdateRate;

    //convert
    int xInt = 0, yInt = 0;
    if (xVal < 1) {
        this->xThreshold += xVal;
        xInt = (int) xThreshold;

        if (xInt >= 1) {
            xThreshold = 0;
        }
    } else {
        xInt = xVal;
        xThreshold = 0;
    }

    if (yVal < 1) {
        this->yThreshold += yVal;
        yInt = (int) yThreshold;

        if (yInt >= 1) {
            yThreshold = 0;
        }
    } else {
        yInt = yVal;
        yThreshold = 0;
    }

    //prepare for moving
    int maxi = Math::max(xInt, yInt);
    int mini = Math::min(xInt, yInt);

    float slope = (mini != 0 && maxi != 0) ? ((float) (mini) / (maxi)) : 0;
    sf::Vector2i lastValidLocation(this->getPhysicX(), this->getPhysicY());

    //move cell by cell on the velocity line
    for (int i = 1; i <= maxi; i++) {
        int smallerIncrease = (int) Math::floor(i * slope);

        int xIncrease, yIncrease;
        if (xInt > yInt) {
            xIncrease = i;
            yIncrease = smallerIncrease;
        }
        else {
            xIncrease = smallerIncrease;
            yIncrease = i;
        }

        int newX = this->getPhysicX() + xIncrease * xModifier;
        int newY = this->getPhysicY() + yIncrease * yModifier;
        

        if (!this->drawboard->isPhysicBlockWithinBound(newX, newY)) {
            //this->drawboard->setElement(this->x, this->y, nullptr);
            return;   
        }
        if (newX == this->getPhysicX() && newY == this->getPhysicY()) {
            continue;
        }

        //get neighbor and do some stuff
        std::shared_ptr<Element> neighbor = this->drawboard->GetByPhysic(newX, newY);
        bool cannotMoveAnymore = this->actOnNeighbor(neighbor, newX, newY, i == maxi, i == 1, 0, lastValidLocation);

        if (cannotMoveAnymore) {
            break;
        }
        lastValidLocation = sf::Vector2i(newX, newY);
    }
}

bool Liquid::actOnNeighbor(std::shared_ptr<Element> neighbor, int neighborPhysX, int neighborPhysY, bool isFinal, bool isFirst, int depth, sf::Vector2i lastLocation) {
    //need some `actOnOther()` crap hereeeee
    if (this->drawboard->isPhysicBlockAir(neighborPhysX, neighborPhysY)) { //this is air, or empty cell, whatever
        this->setAdjacentNeighborFreeFalling(lastLocation, depth);
        if (isFinal) {
            this->isFreeFalling = true;
            this->drawboard->SwapPhysic(this->getPhysicX(), this->getPhysicY(), 
                neighborPhysX, neighborPhysY);
        } else {
            return false;
        }
    }

    else if (neighbor.get()->isLiquid()) { //yay, another liquid, maybe myself...
        Liquid* ne = dynamic_cast<Liquid*>(neighbor.get()); // for keepsake or smth
    }

    else if (neighbor.get()->isSolid()) { //this is what we're talking about

    }

    return false;
}

void Liquid::setAdjacentNeighborFreeFalling(sf::Vector2i lastValidLocation, int depth) {
    if (depth > 0) {
        return;
    }

    std::shared_ptr<Element> leftNeighbor = this->drawboard->GetByPhysic(lastValidLocation.x - 1, lastValidLocation.y);
    if (leftNeighbor != nullptr && leftNeighbor.get()->isSolid()) {
        leftNeighbor.get()->setElementToFreeFalling();
    }

    std::shared_ptr<Element> rightNeighbor = this->drawboard->GetByPhysic(lastValidLocation.x + 1, lastValidLocation.y);
    if (rightNeighbor != nullptr && rightNeighbor.get()->isSolid()) {
        rightNeighbor.get()->setElementToFreeFalling();
    }
}

bool Liquid::isSolid() {
    return false;
}

bool Liquid::isLiquid() {
    return true;
}

bool compareDensity(Liquid* neighbor) {
    
}