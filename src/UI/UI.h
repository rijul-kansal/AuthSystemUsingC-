#pragma once

#include <string>
#include <memory>
#include "Orchestration/IAuthentication.h"
class UI
{
    std::unique_ptr<IAuthentication> auth;
    public:
    UI(std::unique_ptr<IAuthentication> auth) : auth(std::move(auth)) {}
    void start();
    void askingSignUpDetails(std::string& username,std::string& email,std::string& password);
    void askingLoginDetails(std::string& email,std::string& password);
    void askingEmail(std::string& email);
    void askingOTP(std::string& otp);
    void askingPassword(std::string& password);
    AuthResult otpValidation(const std::string& email);
};