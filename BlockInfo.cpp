#include "BlockInfo.h"

std::map<Block::BlockID, sf::Color> Block::BlockInfo::blockColor = {
    {SAND, sf::Color(255, 255, 0, 255)},
    {WATER, sf::Color(37, 150, 190, 255)}
};

float Block::BlockInfo::frameUpdateRate = 1.0/60;

