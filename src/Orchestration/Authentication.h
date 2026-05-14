#pragma once

#include "IAuthentication.h"
#include "User/IUserController.h"
#include "OTPService/IOTPService.h"
#include "Time/ITime.h"
#include <memory>
class Authentication : public IAuthentication
{
    std::shared_ptr<IUserController> userController ;
    std::unique_ptr<IOTPService> otpService ;
    std::shared_ptr<ITime> time;
    public:
    Authentication(std::shared_ptr<IUserController> userController,
                   std::unique_ptr<IOTPService> otpService,
                    std::shared_ptr<ITime> time) 
                   : userController(userController), otpService(std::move(otpService)),
                     time(time) {}
    AuthResult signup(const std::string& username , const std::string& email , const std::string& password) override;
    AuthResult login(const std::string& email , const std::string& password) const override;
    AuthResult generateOTP(const std::string& email) const override;
    AuthResult validateOTP(const std::string& email, const std::string otp,long long time) const override;
    AuthResult changePassword(const std::string& email , const std::string& password) const override;
    AuthResult isVerifiedTrue(const std::string& email) const override;
    virtual long long getTime() const override;
};