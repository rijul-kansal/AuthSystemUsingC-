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
    UserDBResult checkUserAvailableInOTPTable(const std::string& email,const std::string &otp, long long time) override ;
    UserDBResult crudOperationToDB(const std::string& query, const std::vector<std::string>& data) override ;
};
