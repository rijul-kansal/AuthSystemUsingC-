#include "EmailTemplate.h"

std::string EmailTemplate::otpTemplate(const std::string &otp)
{
    std::string htmlBody =
        "<html>"
        "<body>"
        "<p>Hi,</p>"
        "<p>Your OTP for verification is:</p>"
        "<h2 style='color:#2E86C1; letter-spacing:2px;'>" + otp + "</h2>"
        "<p>This OTP is valid for a limited time. Please do not share it with anyone.</p>"
        "<br>"
        "<p>Thank you,<br>Your Security Team</p>"
        "</body>"
        "</html>";
    return htmlBody;
}