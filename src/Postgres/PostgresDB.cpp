#include "PostgresDB.h"
#include "Utility/Messages.h"
#include <cstdlib>
PostgresDB::PostgresDB() : conn(nullptr,PQfinish)
{
    
}

PostgresDBResult PostgresDB::makeConnection()
{
    const char* port = std::getenv("PORT");
    const char* pass = std::getenv("POSTGRES_PASSWORD");
    conn  = PGconnPtr(PQsetdbLogin(
        "localhost",
        port,
        nullptr,
        nullptr,
        "test",
        "postgres",
        pass
    ),PQfinish);

    if (!conn || PQstatus(conn.get()) != CONNECTION_OK) {
        std::string err = conn ? PQerrorMessage(conn.get()) : DefaultMessage::connectionObjNull;
        if (conn) {
            conn = PGconnPtr(nullptr, PQfinish);
        }
        return PostgresDBResult(MessageCodes::ERROR_M, err, {nullptr,PQclear});
    }

    return PostgresDBResult(MessageCodes::SUCCESS, DefaultMessage::connectionSuccess, {nullptr,PQclear});
}

PostgresDBResult PostgresDB::executeCommand(const std::string &query)
{
    if(query.empty())
    {
        return PostgresDBResult(MessageCodes::ERROR_M ,DefaultMessage::QueryStrEmpty, {nullptr,PQclear});   
    }
    
    if(!conn)
    {
        return PostgresDBResult(MessageCodes::ERROR_M ,DefaultMessage::connectionObjEmpty, {nullptr,PQclear});   
    }
    
    PQresultPtr res ( PQexec(conn.get(),query.c_str()), PQclear);
    
    if(!res)
    {
        return PostgresDBResult(MessageCodes::ERROR_M ,DefaultMessage::NoRes, {nullptr,PQclear});   
    }
    
    if(PQresultStatus(res.get()) != PGRES_COMMAND_OK)
    {
        auto x = PQresultErrorMessage(res.get());
        return PostgresDBResult(MessageCodes::ERROR_M ,x, std::move(res));   
    }
    
    return PostgresDBResult(MessageCodes::SUCCESS ,DefaultMessage::QueryExec, std::move(res));   

}

PostgresDBResult PostgresDB::executeCommandWithParams(const std::string &query, const std::vector<std::string >& params)
{
    if(query.empty())
    {
        return PostgresDBResult(MessageCodes::ERROR_M , DefaultMessage::QueryStrEmpty, {nullptr,PQclear});   
    }
    
    if(!conn)
    {
        return PostgresDBResult(MessageCodes::ERROR_M ,DefaultMessage::connectionObjEmpty, {nullptr,PQclear});   
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
        return PostgresDBResult(MessageCodes::ERROR_M ,DefaultMessage::NoRes, {nullptr,PQclear});   
    }
    
    if(PQresultStatus(res.get()) != PGRES_COMMAND_OK && PQresultStatus(res.get()) != PGRES_TUPLES_OK)
    {
        auto x = PQresultErrorMessage(res.get());
        return PostgresDBResult(MessageCodes::ERROR_M ,x, std::move(res));   
    }

    return PostgresDBResult(MessageCodes::SUCCESS ,DefaultMessage::QueryExec, std::move(res));
}

PostgresDB::~PostgresDB()
{
    if(conn)
    {
        PQfinish(conn.get());
    }
}
