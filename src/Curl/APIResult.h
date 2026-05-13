#pragma once

#include "Utility/MessageCodes.h"
#include <string>
class APIResult
{
	MessageCodes code;
	std::string mess;
public:
	APIResult(MessageCodes code , std::string mess) : code(code) , mess(std::move(mess)) {}

	inline MessageCodes getMessageCode() const { return code; }
	inline const std::string& getMessage() const { return mess; }
};
