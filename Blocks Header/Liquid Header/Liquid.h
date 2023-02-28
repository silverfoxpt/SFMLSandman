#ifndef H_LIQUID
#define H_LIQUID

#include "../Element.h"

class Liquid: public Element {
    public:
        Liquid(int x, int y, Block::BlockID id, Drawboard *drawboard) : Element(x, y, id, drawboard) {

        }

        void step() override;
        bool actOnNeighbor(std::shared_ptr<Element> neighbor, int neighborPhysX, int neighborPhysY, bool isFinal, bool isFirst, int depth, sf::Vector2i lastLocation);
        void setAdjacentNeighborFreeFalling(sf::Vector2i lastValidLocation, int depth);

        bool isSolid();
        bool isLiquid();

        //variables
        int density;
        int dispersionRate;
};

#endif