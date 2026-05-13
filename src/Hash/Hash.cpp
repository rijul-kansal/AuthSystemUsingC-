#include "Hash.h"

#include "ExternalLibrary/Bcrypt/bcrypt.h"
std::string Hash::hashPassword(const std::string& password) const
{
    return bcrypt::generateHash(password);
}

bool Hash::validatePassword(const std::string &password, const std::string &hashPass) const
{
    return bcrypt::validatePassword(password,hashPass);
}
