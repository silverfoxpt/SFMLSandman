#ifndef H_ELEMENT
#define H_ELEMENT

#include <SFML/Graphics.hpp>
#include "../BlockInfo.h"
#include "../Drawboard.h"

class Drawboard;

class Element {
    public:
        int x;
        int y;
        float xThreshold;
        float yThreshold;
        sf::Vector2f vel;

        bool isFreeFalling;
        float frictionFactor;

        sf::Color color;
        Block::BlockID id;

        Element(int x, int y, Block::BlockID id, Drawboard *drawboard);

        virtual void step()     = 0;
        //virtual void actOnNeighbor(int newX, int newY) = 0;

        virtual bool isSolid()  = 0;
        virtual bool isLiquid() = 0;

        int getPhysicX();
        int getPhysicY();

        sf::Vector2i convertPhysicToMatrix(int physX, int physY);

    protected:
        Drawboard *drawboard;
        int boardRows;
        int boardCols;
};
#endif