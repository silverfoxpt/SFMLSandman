#include "BlockInfo.h"

std::map<Block::BlockID, sf::Color> Block::BlockInfo::blockColor = {
    {SAND, sf::Color(255, 255, 0, 255)},
    {WATER, sf::Color(37, 150, 190, 255)}
};

