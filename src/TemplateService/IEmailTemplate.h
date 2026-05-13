#pragma once

#include <string>
class IEmailTemplate
{
    public:
    virtual std::string otpTemplate(const std::string& otp) = 0;
    virtual ~IEmailTemplate() = default;
};