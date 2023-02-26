#ifndef H_RANDOM
#define H_RANDOM

#include<random>    
#include<iostream>

#include <cstdlib> 
#include <ctime>



class Random {
    public: 
        static float getRandomFloat()
        {
            static std::default_random_engine e;
            static std::uniform_real_distribution<> dis(0, 1); // rage [0 - 1)
            float x = dis(e); 
            return x;
        }
};

#endif