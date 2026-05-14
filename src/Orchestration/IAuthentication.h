#pragma once


#include "AuthResult.h"
class IAuthentication
{
    public:
    virtual AuthResult signup(const std::string& username , const std::string& email , const std::string& password)=0;
    virtual AuthResult login(const std::string& email , const std::string& password) const = 0;
    virtual AuthResult generateOTP(const std::string& email) const = 0;
    virtual AuthResult validateOTP(const std::string& email, const std::string otp,long long time) const = 0;
    virtual AuthResult changePassword(const std::string& email , const std::string& password) const = 0;
    virtual AuthResult isVerifiedTrue(const std::string& email) const = 0;
    virtual long long getTime() const = 0;
};