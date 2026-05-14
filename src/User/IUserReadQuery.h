#pragma once

#include "UserDbResult.h"
#include <string>
class IUserReadQuery
{
    public:
    virtual UserDBResult checkUserAvailable(const std::string& email) = 0 ;
    virtual UserDBResult checkUserAvailableInOTPTable(const std::string& email,const std::string &otp, long long time) = 0 ;
    virtual ~IUserReadQuery() = default;
};
