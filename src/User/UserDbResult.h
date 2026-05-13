#pragma once
#include "Utility/MessageCodes.h"

#include <string>
class UserDBResult
{
    MessageCodes code;
    std::string message;
    std::string username;
    std::string email;
    std::string hashedPass;
    public:
    UserDBResult( MessageCodes code , 
                  std::string message ,
                  std::string username,
                  std::string email ,
                  std::string hashedPass): 
                code(code) , message(std::move(message)) , 
                username(std::move(username)) , email(std::move(email)) ,
                hashedPass(std::move(hashedPass)) {}
    inline  MessageCodes getMessageCode() const { return code;}
    inline  const std::string& getMessage() const { return message;}
    inline const std::string& getUserName() const {return username ;}
    inline const std::string& getEmail() const {return email ;}
    inline const std::string& getHashedPass() const {return hashedPass ;}
};
