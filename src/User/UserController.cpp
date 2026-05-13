#include "UserController.h"
UserController::UserController(std::unique_ptr<IPasswordValidator> passwordValidator, 
                               std::unique_ptr<IHash> hash, 
                               std::shared_ptr<IUserReadQuery> userReadQuery, 
                               std::shared_ptr<IUserWriteQuery> userWriteQuery) :
                               passwordValidator(std::move(passwordValidator)) , hash(std::move(hash)),
                               userReadQuery(userReadQuery) , userWriteQuery(userWriteQuery)
{
}

UserDBResult UserController::signup(const std::string& username, const std::string& email, const std::string& password)
{
    if(!passwordValidator->isValidPassword(password))
    {
        return UserDBResult(MessageCodes::ERROR_M , "Password not meet the criteria","","","");
    }
    auto hashPass  = hash->hashPassword(password);
    return userWriteQuery->addUserToDB(username,email,hashPass);
}

UserDBResult UserController::login(const std::string& email, const std::string& password) const
{
    auto mess =  userReadQuery->checkUserAvailable(email);
    
    if(mess.getMessageCode() == MessageCodes::ERROR_M)
    {
        return mess;
    }
    auto x  = hash->validatePassword(password , mess.getHashedPass());

    if(x == true)
    {
        return UserDBResult(mess.getMessageCode(), mess.getMessage(), mess.getUserName(),
                mess.getEmail(), "");
    }
    else
    {
        return UserDBResult(MessageCodes::ERROR_M,"Password is incorrect", "", mess.getEmail(), "");
    }
}

UserDBResult UserController::validateOTP(const std::string &email, const std::string &otp) const
{
    return userReadQuery->checkUserAvailableInOTPTable(email,otp);
}

UserDBResult UserController::addOTPToDB(const std::string &email, const std::string &otp)
{
    return userWriteQuery->addOTPToDB(email,otp);
}

UserDBResult UserController::deleteOTPToDB(const std::string &email)
{
    return userWriteQuery->deleteOTPFromDB(email);
}

UserDBResult UserController::changePassword(const std::string &email, const std::string &password) const
{
    if(!passwordValidator->isValidPassword(password))
    {
        return UserDBResult(MessageCodes::ERROR_M , "Password not meet the criteria","","","");
    }
    auto hashPass  = hash->hashPassword(password);
    return userWriteQuery->changeLoginPassword(email,hashPass);
}
