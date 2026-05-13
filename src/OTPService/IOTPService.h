#pragma once

#include <string>
#include "OTPServiceResult.h"
class IOTPService
{
public:
	virtual OTPServiceResult sendOTP(const std::string& email , const std::string& otp) const = 0;
	virtual std::string generateOTP() const = 0 ;
	virtual ~IOTPService() = default;
};
