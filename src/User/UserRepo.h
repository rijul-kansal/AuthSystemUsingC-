#pragma once
#include "IUserWriteQuery.h"
#include "IUserReadQuery.h"
#include "Postgres/IPostgresDB.h"
#include "Time/ITime.h"
#include <memory>
class UserRepo : public IUserWriteQuery , public IUserReadQuery
{
    std::shared_ptr<IPostgresDB> postgresDB ;
    std::shared_ptr<ITime> time;
    public:
    UserRepo(std::shared_ptr<IPostgresDB> postgresDB,std::shared_ptr<ITime> time);
    UserDBResult checkUserAvailable(const std::string& email) override ; 
    UserDBResult checkUserAvailableInOTPTable(const std::string& email,const std::string &otp) override ;
    UserDBResult crudOperationToDB(const std::string& query, const std::vector<std::string>& data) override ;
};
