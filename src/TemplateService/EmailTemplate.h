#pragma once

#include "IEmailTemplate.h"
class EmailTemplate : public IEmailTemplate
{
    public:
    virtual std::string otpTemplate(const std::string& otp) override;
};