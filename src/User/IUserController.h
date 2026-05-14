#pragma once
#include "UserDbResult.h"
#include "nlohmann/json.hpp"
#include <string>
class IUserController
{
    public:
    virtual UserDBResult signup(const std::string& username , const std::string& email , const std::string& password)=0;
    virtual UserDBResult login(const std::string& email , const std::string& password) const = 0;
    virtual UserDBResult addOTPToDB(const std::string &email, const std::string &otp) = 0;
    virtual UserDBResult deleteOTPToDB(const std::string &email) = 0;
    virtual UserDBResult validateOTP(const std::string &email ,const std::string &otp) const = 0;
    virtual UserDBResult changePassword(const std::string& email , const std::string& password) const = 0;
    virtual UserDBResult isVerifiedTrue(const std::string& email ) const = 0;
    virtual ~IUserController() = default;
};
