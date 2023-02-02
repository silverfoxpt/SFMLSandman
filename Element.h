#ifndef H_ELEMENT
#define H_ELEMENT

#include <SFML/Graphics.hpp>
#include "BlockInfo.h"
#include "Drawboard.h"

class Element;

class Element {
    public:
        int x;
        int y;

        sf::Color color;
        Block::BlockID id;

        Element(int x, int y, Block::BlockID id, Drawboard *drawboard);

        virtual void step() = 0;

    protected:
        Drawboard *drawboard;
};
#endif