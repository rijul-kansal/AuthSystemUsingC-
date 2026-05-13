#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "IAPI.h"
#include <curl/curl.h>

class API : public IAPI
{
	std::string apiKey;
public:
	API();
	APIResult emailApi(const std::string& jsonData) const override;
};

