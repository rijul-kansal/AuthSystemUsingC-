#include "RandomNumberGenerator.h"
#include <random>

RandomNumberGenerator::RandomNumberGenerator() : rng(std::random_device{}()) {} 

int RandomNumberGenerator::generateRandomNumber(int no)
{
    if (no <= 0) return -1;
    
    std::uniform_int_distribution<int>  dist(0,no-1);

    return dist(rng); 
}