#include "PostgresDB.h"
#include <cstdlib>
PostgresDB::PostgresDB() : conn(nullptr,PQfinish)
{
    
}

PostgresDBResult PostgresDB::makeConnection()
{
    const char* port = std::getenv("PORT");
    conn  = PGconnPtr(PQsetdbLogin(
        "localhost",
        port,
        nullptr,
        nullptr,
        "test",
        "postgres",
        "Sweethome07@@"
    ),PQfinish);

    if (!conn || PQstatus(conn.get()) != CONNECTION_OK) {
        std::string err = conn ? PQerrorMessage(conn.get()) : "Connection object is null";
        if (conn) {
            conn = PGconnPtr(nullptr, PQfinish);
        }
        return PostgresDBResult(MessageCodes::ERROR_M, err, {nullptr,PQclear});
    }

    return PostgresDBResult(MessageCodes::SUCCESS, "Connection established", {nullptr,PQclear});
}

PostgresDBResult PostgresDB::executeCommand(const std::string &query)
{
    if(query.empty())
    {
        return PostgresDBResult(MessageCodes::ERROR_M ,"Query string is empty", {nullptr,PQclear});   
    }
    
    if(!conn)
    {
        return PostgresDBResult(MessageCodes::ERROR_M ,"Connection is Empty , Please connect to DB again", {nullptr,PQclear});   
    }
    
    PQresultPtr res ( PQexec(conn.get(),query.c_str()), PQclear);
    
    if(!res)
    {
        return PostgresDBResult(MessageCodes::ERROR_M ,"No Result Contact support", {nullptr,PQclear});   
    }
    
    if(PQresultStatus(res.get()) != PGRES_COMMAND_OK)
    {
        auto x = PQresultErrorMessage(res.get());
        return PostgresDBResult(MessageCodes::ERROR_M ,x, std::move(res));   
    }
    
    return PostgresDBResult(MessageCodes::SUCCESS ,"Query executed successfully", std::move(res));   

}

PostgresDBResult PostgresDB::executeCommandWithParams(const std::string &query, const std::vector<std::string >& params)
{
    if(query.empty())
    {
        return PostgresDBResult(MessageCodes::ERROR_M ,"Query string is empty", {nullptr,PQclear});   
    }
    
    if(!conn)
    {
        return PostgresDBResult(MessageCodes::ERROR_M ,"Connection is Empty , Please connect to DB again", {nullptr,PQclear});   
    }
    
    std::vector<const char* > values;

    int sz = params.size();

    values.reserve(sz);

    for(const auto &x : params)
    {
        values.push_back(x.c_str());
    }

    PQresultPtr res(PQexecParams(
        conn.get(),
        query.c_str(),
        sz,
        nullptr,
        values.data(),
        nullptr,
        nullptr,
        0
    ) , PQclear);

    if(!res)
    {
        return PostgresDBResult(MessageCodes::ERROR_M ,"No Result Contact support", {nullptr,PQclear});   
    }
    
    if(PQresultStatus(res.get()) != PGRES_COMMAND_OK && PQresultStatus(res.get()) != PGRES_TUPLES_OK)
    {
        auto x = PQresultErrorMessage(res.get());
        return PostgresDBResult(MessageCodes::ERROR_M ,x, std::move(res));   
    }

    return PostgresDBResult(MessageCodes::SUCCESS ,"Query executed successfully", std::move(res));
}

PostgresDB::~PostgresDB()
{
    if(conn)
    {
        PQfinish(conn.get());
    }
}
