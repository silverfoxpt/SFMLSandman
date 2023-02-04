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
        const static int rows = 512, cols = 512;
        std::vector<std::vector<std::shared_ptr<Element>>> modBox;

        Drawboard();

        void Test();
        void Convert2DPointerTo2DArray();
        void Convert2DArrayTo1DArray();
        sf::Sprite ConvertToSprite();

        std::shared_ptr<Element> getElement(int x, int y);
        void setElement(int x, int y, std::shared_ptr<Element> sh);

        //nice options to have
        bool isLastRow(int x);
        bool isFirstRow(int x);
        bool isLastCol(int y);
        bool isFirstCol(int y);

        //manipulating board
        void StepAll();

    private:    
        sf::Uint8 pixels[rows][4 * cols];
        sf::Uint8 apply[rows * cols * 4];

        sf::Texture tmpTex;
};
#endif