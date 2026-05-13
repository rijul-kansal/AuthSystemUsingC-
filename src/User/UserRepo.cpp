#include "UserRepo.h"
#include "Utility/Queries.h"
UserRepo::UserRepo(std::shared_ptr<IPostgresDB> postgresDB) : postgresDB(postgresDB)
{

}

UserDBResult UserRepo::checkUserAvailable(const std::string& email)
{
    auto mess = postgresDB->executeCommandWithParams(Queries::CHECK_USER , {email});

    if(mess.getMessageCode() == MessageCodes::SUCCESS)
    {
        auto resPtr = mess.takeResult();
        int rows = PQntuples(resPtr.get());

        if(rows == 0)
        {
            return UserDBResult(MessageCodes::ERROR_M, "User not found","",email,"");
        }
        int emailCol = PQfnumber(resPtr.get(), "email");
        int userNameCol = PQfnumber(resPtr.get(), "user_name");
        int passwordCol = PQfnumber(resPtr.get(), "password");
        
        if (emailCol == -1 || userNameCol == -1 || passwordCol == -1) 
        {
            return UserDBResult(MessageCodes::ERROR_M, "Column not found", "" , "","");
        }

        std::string userName   = PQgetvalue(resPtr.get(), 0, userNameCol);
        std::string email  = PQgetvalue(resPtr.get(), 0, emailCol);
        std::string hashedPass  = PQgetvalue(resPtr.get(), 0, passwordCol);
        return UserDBResult(MessageCodes::SUCCESS, "User found",userName,email,hashedPass);
    }
    return UserDBResult(MessageCodes::ERROR_M, mess.getMessage(), "" , "" , "");
}

UserDBResult UserRepo::checkUserAvailableInOTPTable(const std::string &email, const std::string &otp)
{
    auto mess = postgresDB->executeCommandWithParams(Queries::CHECK_USER_OTP_IN_OTP_TABLE , {email,otp});

    if(mess.getMessageCode() == MessageCodes::SUCCESS)
    {
        auto resPtr = mess.takeResult();
        int rows = PQntuples(resPtr.get());

        if(rows == 0)
        {
            return UserDBResult(MessageCodes::ERROR_M, "OTP is wrong","",email,"");
        }
        

        return UserDBResult(MessageCodes::SUCCESS, "OTP validated","",email,"");
    }
    return UserDBResult(MessageCodes::ERROR_M, mess.getMessage(), "" , "" , "");
}

UserDBResult UserRepo::addUserToDB(const std::string &username, const std::string &email, const std::string &password)
{
    auto mess = postgresDB->executeCommandWithParams(Queries::INSERT_NEW_USER , {username,email,password});

    if(mess.getMessageCode() == MessageCodes::ERROR_M)
    {
        return  UserDBResult(mess.getMessageCode(), mess.getMessage() , username,email,"");
    }
    return  UserDBResult(mess.getMessageCode(), "User created successfully",username,email,"");
}

UserDBResult UserRepo::addOTPToDB(const std::string &email, const std::string &otp)
{
    auto mess = postgresDB->executeCommandWithParams(Queries::INSERT_NEW_OTP , {otp,email});
    
    if(mess.getMessageCode() == MessageCodes::ERROR_M)
    {
        return  UserDBResult(mess.getMessageCode(), mess.getMessage() ,"",email,"");
    }
    return  UserDBResult(mess.getMessageCode(), "OTP added successfully","",email,"");
}

UserDBResult UserRepo::deleteOTPFromDB(const std::string &email)
{
    auto mess = postgresDB->executeCommandWithParams(Queries::DELETE_OTP_WITH_EMAIL , {email});

    if(mess.getMessageCode() == MessageCodes::ERROR_M)
    {
        return  UserDBResult(mess.getMessageCode(), mess.getMessage() ,"",email,"");
    }
    return  UserDBResult(mess.getMessageCode(), "OTP deleted successfully","",email,"");
}

UserDBResult UserRepo::changeLoginPassword(const std::string &email, const std::string &password)
{
    auto mess = postgresDB->executeCommandWithParams(Queries::CHANGE_PASSWORD , {email,password});

    if(mess.getMessageCode() == MessageCodes::ERROR_M)
    {
        return  UserDBResult(mess.getMessageCode(), mess.getMessage() ,"",email,"");
    }
    return  UserDBResult(mess.getMessageCode(), "Password changed successfully","",email,"");
}
