#pragma once
#include "IHash.h"
class Hash final : public IHash
{
    public:
    std::string hashPassword(const std::string& password) const override;
    bool validatePassword(const std::string& password, const std::string& hashPass) const override;
};
