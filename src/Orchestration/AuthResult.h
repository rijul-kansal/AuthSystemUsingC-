#pragma once

#include "Utility/MessageCodes.h"

#include <string>
class AuthResult
{
    MessageCodes code;
    std::string message;
    std::string username;
    std::string email;
    public:
    AuthResult(MessageCodes code , std::string message , std::string username, std::string email ) : 
                code(code) , message(std::move(message)) , 
                username(std::move(username)) , email(std::move(email)) {}
    inline  MessageCodes getMessageCode() const { return code;}
    inline  const std::string& getMessage() const { return message;}
    inline const std::string& getUserName() const {return username ;}
    inline const std::string& getEmail() const {return email ;}
};