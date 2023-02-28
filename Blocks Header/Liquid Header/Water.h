#ifndef H_WATER
#define H_WATER

#include "Liquid.h"

class Water : public Liquid {
    public:
        Water(int x, int y, Block::BlockID id, Drawboard *drawboard) : Liquid(x, y, id, drawboard) {
            this->vel = sf::Vector2f(0, -124);
            this->inertialResistance = 0;
            this->frictionFactor = 1.0;
            
            this->density = 5;
            this->dispersionRate = 5;
        }
};

#endif