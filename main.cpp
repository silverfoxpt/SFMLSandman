#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "Element.h"
#include "Drawboard.h"
#include "MovableSolid.h"

//public vars
Drawboard myBoard;

void Test() {
    //test
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 100; j++) {
            MovableSolid tmp(102, 301, Block::BlockID::Sand, &myBoard);
            std::shared_ptr<Element> ptr = std::make_shared<MovableSolid>(tmp);

            myBoard.setElement(i, j, ptr);
        }
    }
    
    //MovableSolid* tmp2 = dynamic_cast<MovableSolid*>(myBoard.getElement(102, 301).get());
    //std::cout << tmp2->x << " " << tmp2->y << " " << tmp2->checker << '\n';
}

void Test2() {
    myBoard.Convert2DPointerTo2DArray();
    myBoard.Convert2DArrayTo1DArray();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    Test();
    Test2(); sf::Sprite spr = myBoard.ConvertToSprite();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        //do shit here
        window.draw(spr);
        myBoard.StepAll();

        window.display();
    }

    return 0;
}