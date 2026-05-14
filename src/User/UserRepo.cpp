#include "UserRepo.h"
#include "Utility/Queries.h"
#include "Utility/Messages.h"
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
        int isVerifiedCol = PQfnumber(resPtr.get(), "is_verified");
        if (emailCol == -1 || userNameCol == -1 || passwordCol == -1 || isVerifiedCol == -1) 
        {
            return UserDBResult(MessageCodes::ERROR_M, DefaultMessage::ColNotFound, "" , "","");
        }

        std::string userName   = PQgetvalue(resPtr.get(), 0, userNameCol);
        std::string email  = PQgetvalue(resPtr.get(), 0, emailCol);
        std::string hashedPass  = PQgetvalue(resPtr.get(), 0, passwordCol);
        std::string isVerified  = PQgetvalue(resPtr.get(), 0, isVerifiedCol);
        if(isVerified == "f")
        {
            return UserDBResult(MessageCodes::ERROR_M, DefaultMessage::userNotVerified,"",email,"");
        }
        return UserDBResult(MessageCodes::SUCCESS, DefaultMessage::userFound,userName,email,hashedPass);
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
            return UserDBResult(MessageCodes::ERROR_M, DefaultMessage::OTPWrong,"",email,"");
        }
        
        return UserDBResult(MessageCodes::SUCCESS, "OTP validated","",email,"");
    }
    return UserDBResult(MessageCodes::ERROR_M, mess.getMessage(), "" , "" , "");
}

UserDBResult UserRepo::crudOperationToDB(const std::string &query, const std::vector<std::string> &data)
{
    auto mess = postgresDB->executeCommandWithParams(query ,data);
    
    if(mess.getMessageCode() == MessageCodes::ERROR_M)
    {
        return  UserDBResult(mess.getMessageCode(), mess.getMessage() ,"","","");
    }
    return  UserDBResult(mess.getMessageCode(), "Added data successfully","","","");
}
