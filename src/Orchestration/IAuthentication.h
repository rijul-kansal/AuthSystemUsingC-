#pragma once


#include "AuthResult.h"
class IAuthentication
{
    public:
    virtual AuthResult signup(const std::string& username , const std::string& email , const std::string& password)=0;
    virtual AuthResult login(const std::string& email , const std::string& password) const = 0;
    virtual AuthResult generateOTP(const std::string& email) const = 0;
    virtual AuthResult validateOTP(const std::string& email, const std::string otp) const = 0;
    virtual AuthResult changePassword(const std::string& email , const std::string& password) const = 0;
};