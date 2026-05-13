#include "UserController.h"
#include "Utility/Queries.h"
#include "Utility/Messages.h"
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
        return UserDBResult(MessageCodes::ERROR_M , DefaultMessage::PasswordCretNotMet,username,email,"");
    }
    auto hashPass  = hash->hashPassword(password);
    auto res = userWriteQuery->crudOperationToDB(Queries::INSERT_NEW_USER,{username,email,hashPass});

    if(res.getMessageCode() == MessageCodes::ERROR_M)
    {
        return res;
    }

    return UserDBResult(res.getMessageCode(), DefaultMessage::userAddedSucc,username,email,"");
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
        return UserDBResult(mess.getMessageCode(),DefaultMessage::LoginSucc, mess.getUserName(),
                mess.getEmail(), "");
    }
    else
    {
        return UserDBResult(MessageCodes::ERROR_M,DefaultMessage::passwordIncorrect, "", mess.getEmail(), "");
    }
}

UserDBResult UserController::validateOTP(const std::string &email, const std::string &otp) const
{
    return userReadQuery->checkUserAvailableInOTPTable(email,otp);
}

UserDBResult UserController::addOTPToDB(const std::string &email, const std::string &otp)
{
    auto res =  userWriteQuery->crudOperationToDB(Queries::INSERT_NEW_OTP ,{otp,email});
    if(res.getMessageCode() == MessageCodes::ERROR_M)
    {
        return res;
    }

    return UserDBResult(res.getMessageCode(), DefaultMessage::OTPAddSucc,"",email,"");
}

UserDBResult UserController::deleteOTPToDB(const std::string &email)
{
    auto res =  userWriteQuery->crudOperationToDB(Queries::DELETE_OTP_WITH_EMAIL, {email});
    if(res.getMessageCode() == MessageCodes::ERROR_M)
    {
        return res;
    }

    return UserDBResult(res.getMessageCode(), DefaultMessage::OTPDelSucc,"",email,"");
}

UserDBResult UserController::changePassword(const std::string &email, const std::string &password) const
{
    if(!passwordValidator->isValidPassword(password))
    {
        return UserDBResult(MessageCodes::ERROR_M , DefaultMessage::PasswordCretNotMet,"","","");
    }
    auto hashPass  = hash->hashPassword(password);
    auto res=  userWriteQuery->crudOperationToDB(Queries::CHANGE_PASSWORD,{email,hashPass});
    if(res.getMessageCode() == MessageCodes::ERROR_M)
    {
        return res;
    }
    return UserDBResult(res.getMessageCode(), DefaultMessage::OTPDelSucc,"",email,"");
}

UserDBResult UserController::isVerifiedTrue(const std::string &email) const
{
    auto res=  userWriteQuery->crudOperationToDB(Queries::MAKE_IS_VERIFIED_TRUE,{email});
    if(res.getMessageCode() == MessageCodes::ERROR_M)
    {
        return res;
    }
    return UserDBResult(res.getMessageCode(), DefaultMessage::VerifySucc,"",email,"");
}
