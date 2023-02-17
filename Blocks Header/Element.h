#ifndef H_ELEMENT
#define H_ELEMENT

#include <SFML/Graphics.hpp>
#include "../Randomizer.h"
#include "../BlockInfo.h"
#include "../Drawboard.h"
#include "../Math.h"

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
        float inertialResistance;

        sf::Color color;
        Block::BlockID id;

        Element(int x, int y, Block::BlockID id, Drawboard *drawboard);

        virtual void step()     = 0;
        virtual bool actOnNeighbor(std::shared_ptr<Element> neighbor, int neighborPhysX, int neighborPhysY, bool isFinal, bool isFirst, int depth, sf::Vector2i lastLocation);
        virtual void setAdjacentNeighborFreeFalling(sf::Vector2i lastValidLocation, int depth);

        virtual bool isSolid()  = 0;
        virtual bool isLiquid() = 0;

        int getPhysicX();
        int getPhysicY();       

        void setElementToFreeFalling(); 

    protected:
        Drawboard *drawboard;
        int boardRows;
        int boardCols;
};
#endif