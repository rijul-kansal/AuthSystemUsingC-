
#include <nlohmann/json.hpp>
#include <cstdlib>
#include "OTPService.h"

using json = nlohmann::json;

OTPServiceResult OTPService::sendOTP(const std::string& receiverEmail , const std::string& otp) const
{
    std::string htmlBody = emailTemplate->otpTemplate(otp);
    auto senderEmail = std::getenv("email_sender_email");
    json body = 
    {
        {"from",senderEmail},
        {"to",receiverEmail},
        {"subject","OTP for verification"},
        {"html",htmlBody}
    };
   
    std::string jsonData = body.dump();
    auto res = api->emailApi(jsonData);

    return OTPServiceResult(res.getMessageCode(), res.getMessage());
}

std::string OTPService::generateOTP() const
{
    std::string ans;
    
    for(int i=0;i<6;i++)
    {
        ans.push_back(randomClass->generateRandomNumber(9)+'0');
    }
    return ans;
}
