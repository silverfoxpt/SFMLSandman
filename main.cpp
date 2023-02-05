#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <chrono>

#include "Drawboard.h"

#include "Sand.h"
#include "Pen.h"

//public vars
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
sf::Sprite mainRenderSprite;

Drawboard myBoard;
int boardPosX = 0;
int boardPosY = 0;

int penSize = 10;
Block::BlockID penID = Block::BlockID::SAND;
Pen myPen(penSize, penID, &myBoard);

std::chrono::high_resolution_clock::time_point start;
std::chrono::high_resolution_clock::time_point end;
float fps;

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

    //test 2
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

void RenderSimulation() {
    //do shit here
    window.draw(mainRenderSprite);
    
    myBoard.StepAll();
    Test();
    UpdateBoard(); mainRenderSprite = myBoard.ConvertToSprite();
    mainRenderSprite.setPosition(boardPosX, boardPosY);
}

int main()
{
    UpdateBoard(); mainRenderSprite = myBoard.ConvertToSprite();

    while (window.isOpen())
    {
        start = std::chrono::high_resolution_clock::now();

        //event stuff
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed: {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                        int x = worldPos.x;
                        int y = worldPos.y;

                        x -= boardPosX; y -= boardPosY;
                        myPen.Draw(y, x);
                    }
                    break;
                }                    
                default:
                    break;
            }
        }

        //render stuff
        window.clear(sf::Color(50, 50, 50, 255));
        RenderSimulation();
        window.display();

        //time stuff
        end = std::chrono::high_resolution_clock::now();
        fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
        std::cout << fps << '\n';
    }

    return 0;
}