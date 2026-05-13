#pragma once

#include "./IRandomNumberGenerator.h"
#include <random>
class RandomNumberGenerator : public IRandomNumberGenerator
{
    std::mt19937 rng;
    public:
    RandomNumberGenerator();
    int generateRandomNumber(int) override;
};
