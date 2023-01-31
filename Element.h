#ifndef H_ELEMENT
#define H_ELEMENT

#include <SFML/Graphics.hpp>

class Element {
    public:
        int x;
        int y;
        sf::Color color;

        Element(int x, int y) {
            
        }

        virtual void Update();
};
#endif