#ifndef H_BLOCKINFO
#define H_BLOCKINFO

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

//WARNING: NEVER, EVER INCLUDE ANY TYPE OF CUSTOM HEADER HERE. CROSS-REFERENCING WILL MAKE YOUR LIFE UTTERLY SHIT :)

namespace Block {
    enum BlockID {
        SAND,
        WATER
    };

    class BlockInfo {
        public:
            static std::map<BlockID, sf::Color> blockColor;
    };
}

#endif