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

class Drawboard {
    public:
        void Test();
        void ApplyToArray();
        sf::Sprite ConvertToSprite();

    private:    
        const static int rows = 512, cols = 512;
        sf::Uint8 pixels[rows][4 * cols];
        sf::Uint8 apply[rows * cols * 4];

        sf::Texture tmpTex;
};

#endif