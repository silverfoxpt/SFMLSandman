#ifndef H_LIQUID
#define H_LIQUID

#include "../Element.h"

class Liquid: public Element {
    public:
        Liquid(int x, int y, Block::BlockID id, Drawboard *drawboard) : Element(x, y, id, drawboard) {

        }

        void step() override;
        bool isSolid();
        bool isLiquid();
};

#endif