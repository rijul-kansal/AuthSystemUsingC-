#include "PasswordValidator.h"

bool PasswordValidator::isValidPassword(const std::string& password) const 
{
    if(password.length() <= 6) return false;

    bool isDigit = false;
    bool isUpperCase = false;
    bool isLowerCase = false;
    bool isSpecialChar = false;

    for(auto x: password)
    {
        if(x>='A' && x<='Z') 
            isUpperCase = true;
        else if(x>='a' && x<='z') 
            isLowerCase = true;
        else if(x>='0' && x<='9') 
            isDigit = true;
        else
            isSpecialChar = true;
    }

    return isDigit && isUpperCase && isLowerCase && isSpecialChar;
}