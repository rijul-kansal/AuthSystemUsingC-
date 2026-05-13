#include "Authentication.h"

AuthResult Authentication::signup(const std::string &username, const std::string &email, const std::string &password)
{
    auto res = userController->signup(username,email,password);
    return AuthResult(res.getMessageCode() , res.getMessage(), res.getUserName() , res.getEmail());
}

AuthResult Authentication::login(const std::string &email, const std::string &password) const
{
    auto res = userController->login(email,password);
    return AuthResult(res.getMessageCode() , res.getMessage(), res.getUserName() , res.getEmail());
}

AuthResult Authentication::generateOTP(const std::string &email) const
{
    // Generate OTP
    auto otp = otpService->generateOTP();
    // save OTP to DB
    auto otpSaver = userController->addOTPToDB(email,otp);
    if(otpSaver.getMessageCode()  == MessageCodes::ERROR_M)
    {
        return AuthResult(otpSaver.getMessageCode(), otpSaver.getMessage(),"",email);
    }
    
    // save OTP to email
    auto sendOTPTOEmailRes = otpService->sendOTP(email,otp);
    
    if(sendOTPTOEmailRes.getMessageCode() == MessageCodes::ERROR_M)
    {
        return AuthResult(sendOTPTOEmailRes.getMessageCode(), sendOTPTOEmailRes.getMessage(),"",email);
    }
    return AuthResult(MessageCodes::SUCCESS, "Successfully sent OTP","",email);
}

AuthResult Authentication::validateOTP(const std::string &email, const std::string otp) const
{
    auto validateOTPRes = userController->validateOTP(email,otp);

    if(validateOTPRes.getMessageCode() == MessageCodes::ERROR_M)
    {
        return AuthResult(validateOTPRes.getMessageCode(), validateOTPRes.getMessage(),"",email);
    }
    
    // delete OTP
    auto deleteOTPRes = userController->deleteOTPToDB(email);
    return AuthResult(MessageCodes::SUCCESS, "OTP validated successfully","",email);
}

AuthResult Authentication::changePassword(const std::string &email, const std::string &password) const
{
    auto res =  userController->changePassword(email,password);

    if(res.getMessageCode() == MessageCodes::ERROR_M)
    {
        return AuthResult(res.getMessageCode(),res.getMessage(),"",email);
    }
    return AuthResult(res.getMessageCode(),"Password changed successfully","",email);
}
