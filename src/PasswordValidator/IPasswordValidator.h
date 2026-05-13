#pragma once

#include <string>
class IPasswordValidator
{
    public:
    virtual bool isValidPassword(const std::string& password) const = 0;
    virtual ~IPasswordValidator()= default;
};
