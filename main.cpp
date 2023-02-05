#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "Drawboard.h"

#include "Element.h"
#include "MovableSolid.h"
#include "Sand.h"

//public vars
Drawboard myBoard;
int boardPosX = 150;
int boardPosY = 100;

void Test() {
    //test
    /*for (int i = 100; i < 200; i++) {
        for (int j = 100; j < 200; j++) {
            MovableSolid tmp(i, j, Block::BlockID::Sand, &myBoard);
            std::shared_ptr<Element> ptr = std::make_shared<MovableSolid>(tmp);

            myBoard.setElement(i, j, ptr);
        }
    }*/
    
    //MovableSolid* tmp2 = dynamic_cast<MovableSolid*>(myBoard.getElement(102, 301).get());
    //std::cout << tmp2->x << " " << tmp2->y << " " << tmp2->checker << '\n';

    Sand tmp(100, 100, Block::BlockID::SAND, &myBoard);
    std::shared_ptr<Element> ptr = std::make_shared<MovableSolid>(tmp);

    myBoard.setElement(100, 100, ptr);
    

    tmp = Sand(200, 200, Block::BlockID::SAND, &myBoard);
    ptr = std::make_shared<MovableSolid>(tmp);

    myBoard.setElement(200, 200, ptr);

    tmp = Sand(300, 300, Block::BlockID::SAND, &myBoard);
    ptr = std::make_shared<MovableSolid>(tmp);

    myBoard.setElement(300, 300, ptr);
}

void UpdateBoard() {
    myBoard.Convert2DPointerTo2DArray();
    myBoard.Convert2DArrayTo1DArray();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    //Test();
    UpdateBoard(); sf::Sprite spr = myBoard.ConvertToSprite();

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
        Test();
        UpdateBoard(); spr = myBoard.ConvertToSprite();
        spr.setPosition(boardPosX, boardPosY);

        window.display();
    }

    return 0;
}