#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Element.h"

const int rows = 512, cols = 512;
sf::Uint8 f[rows][4 * cols];

void Initialize() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j % 2 == 0) {
                //white
                f[i][j] = f[i][j+1] = f[i][j+2] = f[i][j+3] = 255;
            } else {
                f[i][j] = f[i][j+1] = f[i][j+2] = 0;
                f[i][j+3] = 255;
            }
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    Initialize();
    sf::Image img; img.create(cols, rows, f);
    sf::RenderTexture tex; tex.create(cols, rows); tex.clear(); tex.draw(img); tex.display();

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
        window.draw(img);

        window.display();
    }

    return 0;
}