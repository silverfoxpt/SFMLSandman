#ifndef H_MATH
#define H_MATH

#include <math.h>
#include <SFML/Graphics.hpp>

class Math {
    public:
        static float abs(float x) {
            return fabs(x);
        }

        static float max(float a, float b) {
            return std::max(a, b);
        }

        static float min(float a, float b) {
            return std::min(a, b);
        }

        static void addVector(sf::Vector2f &first, sf::Vector2f sec) {
            first.x += sec.x;    
            first.y += sec.y;
        }

        static float floor(float x) {
            return std::floor(x);
        }

        static float ceil(float x) {
            return std::ceil(x);
        }

        static float mag(sf::Vector2f vec) {
            return std::sqrt(vec.x * vec.x + vec.y * vec.y);
        }

        static sf::Vector2f normalize(sf::Vector2f vec) {
            float magnitude = mag(vec);
            return sf::Vector2f(vec.x / magnitude, vec.y / magnitude);
        }
};


#endif