#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Element.h"
#include "Drawboard.h"

//public vars
Drawboard myBoard;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    myBoard.Test();
    myBoard.ApplyToArray();
    sf::Sprite spr = myBoard.ConvertToSprite();

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