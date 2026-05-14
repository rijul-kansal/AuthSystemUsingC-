#include "API.h"
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <memory>
#include "Utility/Messages.h"

using CURLPtr = std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>; 
using HeaderPtr = std::unique_ptr<curl_slist, decltype(&curl_slist_free_all)>;


API::API()
{
    const char* apiKeyk = std::getenv("SEND_EMAIL_API_KEY");
    if (apiKeyk == nullptr)
    {
        apiKey = "";
    }
    else
    {
        apiKey = apiKeyk;
    }
}

APIResult API::emailApi(const std::string& jsonData) const
{
    CURLPtr curl = CURLPtr(curl_easy_init() , curl_easy_cleanup);

    if (!curl)
    {
        return APIResult(MessageCodes::ERROR_M, DefaultMessage::NoCurl);
    }
    HeaderPtr headers(nullptr, curl_slist_free_all);

    std::string authHeader =
        "Authorization: Bearer " + apiKey;

    headers.reset(
        curl_slist_append(
            headers.release(),
            authHeader.c_str()
        )
    );

    headers.reset(
        curl_slist_append(
            headers.release(),
            "Content-Type: application/json"
        )
    );

    auto url =  std::getenv("SEND_EMAIL_API_URL");
    curl_easy_setopt(
        curl.get(),
        CURLOPT_URL,
        url
    );

    curl_easy_setopt(
        curl.get(),
        CURLOPT_HTTPHEADER,
        headers.get()
    );

    curl_easy_setopt(
        curl.get(), 
        CURLOPT_TIMEOUT, 
        10L);

    curl_easy_setopt(
        curl.get(),
        CURLOPT_POSTFIELDS,
        jsonData.c_str()
    );

    CURLcode res = curl_easy_perform(curl.get());

    if (res != CURLE_OK)
    {
        return APIResult(MessageCodes::ERROR_M, curl_easy_strerror(res));
    }


    long statusCode = 0;
    CURLcode statusRes = curl_easy_getinfo(
        curl.get(),
        CURLINFO_RESPONSE_CODE,
        &statusCode
    );

    if (statusRes != CURLE_OK)
    {
        return APIResult(
            MessageCodes::ERROR_M,
            "Failed to get HTTP status code"
        );
    }

    if (statusCode >= 200 && statusCode < 300)
    {
        return APIResult(
            MessageCodes::SUCCESS,
            "Email sent successfully"
        );
    }

    if (statusCode == 401)
    {
        return APIResult(
            MessageCodes::ERROR_M,
            "Unauthorized API key"
        );
    }

    if (statusCode == 403)
    {
        return APIResult(
            MessageCodes::ERROR_M,
            "Access forbidden"
        );
    }

    if (statusCode == 429)
    {
        return APIResult(
            MessageCodes::ERROR_M,
            "Rate limit exceeded"
        );
    }

    if (statusCode >= 500)
    {
        return APIResult(
            MessageCodes::ERROR_M,
            "Server error from Resend API"
        );
    }

    return APIResult(
        MessageCodes::ERROR_M,
        "Unknown HTTP error"
    );
}

