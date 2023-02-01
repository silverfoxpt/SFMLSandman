#ifndef H_ELEMENT
#define H_ELEMENT

#include <SFML/Graphics.hpp>
#include "BlockInfo.h"

class Element {
    public:
        int x;
        int y;

        sf::Color color;
        Block::BlockID id;

        Element(int x, int y, Block::BlockID id);

        virtual void Update();
};
#endif