#ifndef H_ELEMENT
#define H_ELEMENT

#include <SFML/Graphics.hpp>

class Element {
    public:
        int x;
        int y;
        sf::Color color;

        virtual void Update() = 0;
        virtual void Draw() = 0;
};
#endif