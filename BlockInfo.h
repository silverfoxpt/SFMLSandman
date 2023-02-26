#ifndef H_BLOCKINFO
#define H_BLOCKINFO

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>
#include "Randomizer.h"

//WARNING: NEVER, EVER INCLUDE ANY TYPE OF CUSTOM HEADER HERE. CROSS-REFERENCING WILL MAKE YOUR LIFE UTTERLY SHIT :)

namespace Block {
    enum BlockID {
        SAND,
        WATER
    };

    class BlockInfo {
        public:
            static std::map<BlockID, std::vector<sf::Color>> blockColor;
            
            //static sf::Vector2f normalGravity;
            static float frameUpdateRate;

            static sf::Color randomPickColor(Block::BlockID id);
    };
}

#endif