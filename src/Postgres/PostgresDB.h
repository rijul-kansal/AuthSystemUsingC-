#ifndef POSTGRES_DB_H
#define POSTGRES_DB_H

#include <libpq-fe.h>
#include "IPostgresDB.h"
#include <memory>
using PGconnPtr = std::unique_ptr<PGconn,decltype(&PQfinish)>; 
class PostgresDB : public IPostgresDB
{
    PGconnPtr conn;
    public:
    PostgresDB();
    PostgresDBResult makeConnection()  override;
    PostgresDBResult executeCommand(const std::string& query)  override;
    PostgresDBResult executeCommandWithParams(const std::string& query, 
                                                      const std::vector< std::string>& params)  override;
    ~PostgresDB();
};
#endif