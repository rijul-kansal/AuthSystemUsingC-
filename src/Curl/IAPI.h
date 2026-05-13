#pragma once

#include "APIResult.h"

class IAPI
{
public:
	virtual APIResult emailApi(const std::string& jsonData) const = 0;
	virtual ~IAPI() = default;
};

