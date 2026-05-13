#pragma once


class IRandomNumberGenerator
{
    public:
    virtual int generateRandomNumber(int)=0;
    virtual ~IRandomNumberGenerator() = default;
};
