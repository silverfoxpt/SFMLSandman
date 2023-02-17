#ifndef H_MOVABLESOLID
#define H_MOVABLESOLID

#include "../Solid.h"

class MovableSolid : public Solid{
    public:
        MovableSolid(int x, int y, Block::BlockID id, Drawboard *drawboard) : Solid(x, y, id, drawboard) {
            
        }

        void step() override;
        bool actOnNeighbor(std::shared_ptr<Element> neighbor, int neighborPhysX, int neighborPhysY, bool isFinal, bool isFirst, int depth, sf::Vector2i lastLocation) override;
        void setAdjacentNeighborFreeFalling(sf::Vector2i lastValidLocation, int depth) override;

    private:
};

#endif