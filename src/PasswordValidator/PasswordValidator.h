#pragma once

#include "IPasswordValidator.h"
class PasswordValidator : public IPasswordValidator
{
    public:
    bool isValidPassword(const std::string& password) const override;
};
