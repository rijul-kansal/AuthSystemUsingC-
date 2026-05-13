#pragma once

#include "IOTPService.h"
#include "Curl/API.h"
#include "RandomClass/IRandomNumberGenerator.h"
#include "TemplateService/IEmailTemplate.h"
#include <string>
#include <memory>
class OTPService : public IOTPService	
{
	std::shared_ptr<IAPI> api;
	std::shared_ptr<IRandomNumberGenerator> randomClass;
	std::shared_ptr<IEmailTemplate> emailTemplate;
public:
	OTPService(std::shared_ptr<IAPI> api,
			   std::shared_ptr<IRandomNumberGenerator> randomClass,
			   std::shared_ptr<IEmailTemplate> emailTemplate ) :
				api(api) , randomClass(randomClass) , emailTemplate(emailTemplate) {}
	OTPServiceResult sendOTP(const std::string& email , const std::string& otp) const override;
	std::string generateOTP() const override;
};
