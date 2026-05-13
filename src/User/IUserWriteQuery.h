#pragma once

#include "UserDbResult.h"
#include <string>
class IUserWriteQuery
{
    public:
    virtual UserDBResult addUserToDB(const std::string& username, const std::string& email , const std::string& password) = 0 ;
    virtual UserDBResult addOTPToDB(const std::string& email , const std::string& otp) = 0 ;
    virtual UserDBResult deleteOTPFromDB(const std::string& email ) = 0 ;
    virtual UserDBResult changeLoginPassword(const std::string& email, const std::string& password ) = 0 ;
};