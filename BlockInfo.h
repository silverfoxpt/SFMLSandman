#ifndef H_BLOCKINFO
#define H_BLOCKINFO

#include <SFML/Graphics.hpp>
#include <map>

namespace Block {
    enum BlockID {
        Sand
    };

    class BlockInfo {
        public:
           static std::map<BlockID, sf::Color> blockColor;
    };
}

#endif