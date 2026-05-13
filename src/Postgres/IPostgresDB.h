#pragma once

#include <vector>
#include "PostgresDBResult.h"
class IPostgresDB
{
    public:
    virtual PostgresDBResult makeConnection() = 0;
    virtual PostgresDBResult executeCommand(const std::string& query)  = 0;
    virtual PostgresDBResult executeCommandWithParams(const std::string& query, 
                                                      const std::vector< std::string>& params)  =0;
};