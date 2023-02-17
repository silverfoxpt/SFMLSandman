#ifndef H_RANDOM
#define H_RANDOM

#include<random>    

class Random {
    public: 
        static float getRandomFloat()
        {
            static std::default_random_engine e;
            static std::uniform_real_distribution<> dis(0, 1); // rage [0 - 1)
            return dis(e);
        }
};

#endif