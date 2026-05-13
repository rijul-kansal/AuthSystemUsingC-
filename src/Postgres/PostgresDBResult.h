#pragma once
#include <string>
#include <memory>
#include <libpq-fe.h>
#include "Utility/MessageCodes.h"

using PQresultPtr = std::unique_ptr<PGresult , decltype(&PQclear)>;
class PostgresDBResult
{
    MessageCodes code;
    std::string message;
    PQresultPtr res;
    public:
    PostgresDBResult(MessageCodes code , std::string message , PQresultPtr res) : 
                code(code) , message(std::move(message)) , res(std::move(res)) {}
    inline  MessageCodes getMessageCode() const { return code;}
    inline  const std::string& getMessage() const { return message;}
    inline  PQresultPtr takeResult() { return std::move(res);}
};