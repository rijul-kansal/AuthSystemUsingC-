#pragma once
#include "IUserController.h"
#include "PasswordValidator/IPasswordValidator.h"
#include "Hash/IHash.h"
#include "IUserReadQuery.h"
#include "IUserWriteQuery.h"

#include <memory>
class UserController: public IUserController
{
    std::unique_ptr<IPasswordValidator> passwordValidator;
    std::unique_ptr<IHash> hash;
    std::shared_ptr<IUserReadQuery> userReadQuery;
    std::shared_ptr<IUserWriteQuery> userWriteQuery;
    public:
    UserController(std::unique_ptr<IPasswordValidator> passwordValidator,
    std::unique_ptr<IHash> hash,
    std::shared_ptr<IUserReadQuery> userReadQuery,
    std::shared_ptr<IUserWriteQuery> userWriteQuery);
    UserDBResult signup(const std::string& username , const std::string& email , const std::string& password) override;
    UserDBResult login(const std::string& email , const std::string& password)const  override;
    UserDBResult validateOTP(const std::string &email,const std::string &otp) const override;
    UserDBResult addOTPToDB(const std::string &email, const std::string &otp) override;
    UserDBResult deleteOTPToDB(const std::string &email) override;
    UserDBResult changePassword(const std::string& email , const std::string& password) const override;
};
