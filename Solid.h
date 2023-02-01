#ifndef H_SOLID
#define H_SOLID

#include "Element.h"
#include "BlockInfo.h"

class Solid : public Element {
    public:
        Solid(int x, int y, Block::BlockID id) : Element(x, y, id) {
            //nothing here...   
        }
};

#endif