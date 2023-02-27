#include "BlockInfo.h"

std::map<Block::BlockID, std::vector<sf::Color>> Block::BlockInfo::blockColor = {
    {SAND, 
        {
            sf::Color(167, 182, 0, 255),

            sf::Color(220, 215, 212, 255),
            sf::Color(220, 215, 212, 255),

            sf::Color(221, 230, 39, 255),
            sf::Color(221, 230, 39, 255),
            sf::Color(221, 230, 39, 255),
            sf::Color(221, 230, 39, 255),
        }
    },
    {WATER, 
        {
            //sf::Color(0, 147, 183, 150),

            sf::Color(99, 205, 215, 220),
            //sf::Color(99, 205, 215, 255),
            //sf::Color(99, 205, 215, 255),
            //sf::Color(99, 205, 215, 255),

            //sf::Color(160, 197, 207, 255)
        }
    }
};

float Block::BlockInfo::frameUpdateRate = 1.0/60;

sf::Color Block::BlockInfo::randomPickColor(Block::BlockID id) {
    std::vector<sf::Color> colors = blockColor[id];

    float rand = Random::getRandomFloat();
    float threshold = 1.0/colors.size();

    for (int i = 0 ; i < (int) colors.size(); i++) {
        if (rand <= threshold * (i+1)) {
            return colors[i];
        }
    }
    return colors[colors.size() - 1];
}

Block::BlockID Block::BlockInfo::intToId(int x) {
    try {
        Block::BlockID id = static_cast<Block::BlockID>(x);
        return id;
    } catch(...) {
        std::cout << "ID not found";
    }
}

