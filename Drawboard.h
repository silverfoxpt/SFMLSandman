#ifndef H_DRAW
#define H_DRAW

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

#include <cstdlib>
#include <ctime>

#include <memory>

#include "Element.h"

class Element;

class Drawboard {
    public:
        Drawboard();

        void Test();
        void ApplyToArray();

        std::shared_ptr<Element> getElement(int x, int y);
        void setElement(int x, int y, std::shared_ptr<Element> sh);

        sf::Sprite ConvertToSprite();

        std::vector<std::vector<std::shared_ptr<Element>>> modBox;

    private:    
        const static int rows = 512, cols = 512;
        sf::Uint8 pixels[rows][4 * cols];
        sf::Uint8 apply[rows * cols * 4];

        sf::Texture tmpTex;
};
#endif