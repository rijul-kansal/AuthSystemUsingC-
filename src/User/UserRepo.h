#pragma once
#include "IUserWriteQuery.h"
#include "IUserReadQuery.h"
#include "Postgres/IPostgresDB.h"

#include <memory>
class UserRepo : public IUserWriteQuery , public IUserReadQuery
{
    std::shared_ptr<IPostgresDB> postgresDB ;
    public:
    UserRepo(std::shared_ptr<IPostgresDB> postgresDB);
    UserDBResult checkUserAvailable(const std::string& email) override ; 
    UserDBResult checkUserAvailableInOTPTable(const std::string& email,const std::string &otp) override ;
    UserDBResult addUserToDB(const std::string& username, const std::string& email , const std::string& password)  override ;
    UserDBResult addOTPToDB(const std::string& email , const std::string& otp) override ;
    UserDBResult deleteOTPFromDB(const std::string& email ) override ;
    UserDBResult changeLoginPassword(const std::string& email, const std::string& password ) override ;
};
