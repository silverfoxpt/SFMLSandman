#include "../../../Blocks Header/Solid Header/Movable Solid Header/MovableSolid.h"

void MovableSolid::step()  {
    int x = this->x;
    if (this->drawboard->isLastRow(x)) {
        return;
    }
    
    //damp x
    if (this->isFreeFalling) {
        this->vel.x *= 0.9;
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

    float slope = (mini != 0 && maxi != 0) ? (float) mini / maxi : 0;
    sf::Vector2i lastValidLocation(this->getPhysicX(), this->getPhysicY());

    //move cell by cell on the velocity line
    for (int i = 1; i <= maxi; i++) {
        int smallerIncrease = (int) (i * slope);

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
            this->drawboard->setElement(this->x, this->y, nullptr);
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

bool MovableSolid::actOnNeighbor(std::shared_ptr<Element> neighbor, int neighborPhysX, int neighborPhysY, bool isFinal, bool isFirst, int depth, sf::Vector2i lastLocation) {
    if (this->drawboard->isPhysicBlockAir(neighborPhysX, neighborPhysY)) { //is air
        this->setAdjacentNeighborFreeFalling(lastLocation, depth);
        if (isFinal) {
            this->drawboard->OverridePhysic(this->getPhysicX(), this->getPhysicY(), neighborPhysX, neighborPhysY);
        }
        this->isFreeFalling = true;
        return false;
    }

    else if (neighbor.get()->isLiquid()) {
        this->isFreeFalling = true;
        if (depth > 0) {
            //this->setAdjacentNeighborFreeFalling(lastLocation, depth); //stupid shit
            this->drawboard->SwapPhysic(this->getPhysicX(), this->getPhysicY(), neighborPhysX, neighborPhysY);
            return false;
        } else {
            this->drawboard->SwapPhysicTriple(this->getPhysicX(), this->getPhysicY(), 
                neighborPhysX, neighborPhysY,
                lastLocation.x, lastLocation.y
            );
            return true;
        }
    }

    else if (neighbor.get()->isSolid()) {
        if (depth > 0) {
            return true;
        }
        if (isFinal) {
            this->drawboard->OverridePhysic(this->getPhysicX(), this->getPhysicY(), lastLocation.x, lastLocation.y);
            return true;
        }

        //transfer some vertical into horizontal force
        if (this->isFreeFalling) {
            float absY = Math::max(Math::abs(vel.y) / 31, 105);
            this->vel.x = (this->vel.x < 0) ? -absY : absY;
        }
        
        //get integer velocity
        sf::Vector2f norm = Math::normalize(this->vel);

        int additionalX = Math::abs(norm.x) > 0.1 
            ? (norm.x < 0 ? Math::floor(norm.x) : Math::ceil(norm.x))
            : (0);
        int additionalY = Math::abs(norm.y) > 0.1 
            ? (norm.y < 0 ? Math::floor(norm.y) : Math::ceil(norm.y))
            : (0);

        //add some friction
        vel.x *= this->frictionFactor * neighbor.get()->frictionFactor;

        //CHECK CLOSEST DIAGONAL NEIGHBOR
        int diagX = this->getPhysicX() + additionalX;
        int diagY = this->getPhysicY() + additionalY;
        std::shared_ptr<Element> diag = this->drawboard->GetByPhysic(diagX, diagY);

        if (this->drawboard->isPhysicBlockAir(diagX, diagY) || diag != nullptr) {
            bool stoppedDiagonally = this->actOnNeighbor(diag, diagX, diagY, true, false, depth+1, lastLocation);
            if (!stoppedDiagonally) {
                this->isFreeFalling = true;
                return true;
            }
        }

        //CHECK CLOSEST ADJACENT NEIGHBOR
        int adjX = this->getPhysicX() + additionalX;
        int adjY = this->getPhysicY();
        std::shared_ptr<Element> adj = this->drawboard->GetByPhysic(adjX, adjY);

        if (this->drawboard->isPhysicBlockAir(adjX, adjY) || adj != nullptr) {
            bool stoppedAdjacent = this->actOnNeighbor(adj, adjX, adjY, true, false, depth+1, lastLocation);
            this->isFreeFalling = false;

            if (stoppedAdjacent) {
                this->vel.x *= -1;
                this->drawboard->OverridePhysic(this->getPhysicX(), this->getPhysicY(), lastLocation.x, lastLocation.y);
            }
            return true;
        }
    }
    return false;
}

void MovableSolid::setAdjacentNeighborFreeFalling(sf::Vector2i lastValidLocation, int depth) {
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