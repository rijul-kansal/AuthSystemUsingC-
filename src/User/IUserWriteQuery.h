#pragma once

#include "UserDbResult.h"
#include <string>
#include <vector>
class IUserWriteQuery
{
    public:
    virtual UserDBResult crudOperationToDB(const std::string& query, const std::vector<std::string>& data) = 0 ;
};