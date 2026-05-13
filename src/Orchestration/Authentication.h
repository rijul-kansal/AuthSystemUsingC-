#pragma once

#include "IAuthentication.h"
#include "User/IUserController.h"
#include "OTPService/IOTPService.h"
#include <memory>
class Authentication : public IAuthentication
{
    std::shared_ptr<IUserController> userController ;
    std::unique_ptr<IOTPService> otpService ;
    public:
    Authentication(std::shared_ptr<IUserController> userController,
                   std::unique_ptr<IOTPService> otpService) 
                   : userController(userController), otpService(std::move(otpService)) {}
    AuthResult signup(const std::string& username , const std::string& email , const std::string& password) override;
    AuthResult login(const std::string& email , const std::string& password) const override;
    AuthResult generateOTP(const std::string& email) const override;
    AuthResult validateOTP(const std::string& email, const std::string otp) const override;
    AuthResult changePassword(const std::string& email , const std::string& password) const override;
};