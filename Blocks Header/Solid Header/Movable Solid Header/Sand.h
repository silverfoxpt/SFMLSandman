#ifndef H_SAND
#define H_SAND

#include "MovableSolid.h"
#include "../../../Randomizer.h"

class Sand : public MovableSolid {
    public:
        Sand(int x, int y, Block::BlockID id, Drawboard *drawboard) : MovableSolid(x, y, id, drawboard) {
            this->frictionFactor = 0.9;
            this->inertialResistance = 0.5f;

            this->isFreeFalling = true;
            this->vel = sf::Vector2f(Random::getRandomFloat() >= 0.5 ? 1 : -1, -125.0);
        }
};

#endif