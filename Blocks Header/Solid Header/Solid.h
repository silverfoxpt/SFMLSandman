#ifndef H_SOLID
#define H_SOLID

#include "../Element.h"
#include "../../BlockInfo.h"

class Solid : public Element {
    public:
        Solid(int x, int y, Block::BlockID id, Drawboard *drawboard) : Element(x, y, id, drawboard) {
            //nothing here...   
        }

        bool isSolid() override;
        bool isLiquid() override;
};

#endif