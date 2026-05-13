#pragma once

#include <string>
class IHash
{
    public:
    virtual std::string hashPassword(const std::string& password) const = 0;
    virtual bool validatePassword(const std::string& password, const std::string& hashPass) const = 0;
    virtual ~IHash()= default;
};
