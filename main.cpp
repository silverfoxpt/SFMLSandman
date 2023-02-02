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

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    myBoard.Test();
    myBoard.ApplyToArray();
    sf::Sprite spr = myBoard.ConvertToSprite();

    //
    MovableSolid tmp(0, 2, Block::BlockID::Sand, &myBoard);
    std::shared_ptr<Element> ptr = std::make_shared<MovableSolid>(tmp);
    
    MovableSolid* tmp2 = dynamic_cast<MovableSolid*>(ptr.get());
    std::cout << tmp2->x << " " << tmp2->y << " " << tmp2->checker << '\n';

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

        window.display();
    }

    return 0;
}