#include "Postgres/PostgresDB.h"
#include "Postgres/IPostgresDB.h"
#include "Utility/MessageCodes.h"
#include "Utility/Queries.h"

#include "PasswordValidator/IPasswordValidator.h"
#include "PasswordValidator/PasswordValidator.h"

#include "Hash/IHash.h"
#include "Hash/Hash.h"

#include "User/UserRepo.h"
#include "User/IUserReadQuery.h"
#include "User/IUserWriteQuery.h"
#include "User/IUserController.h"
#include "User/UserController.h"

#include "RandomClass/IRandomNumberGenerator.h"
#include "RandomClass/RandomNumberGenerator.h"

#include "Curl/API.h"
#include "Curl/IAPI.h"

#include "TemplateService/IEmailTemplate.h"
#include "TemplateService/EmailTemplate.h"


#include "OTPService/IOTPService.h"
#include "OTPService/OTPService.h"

#include "Orchestration/Authentication.h"
#include "Orchestration/IAuthentication.h"
#include "UI/UI.h"

#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <memory>

// >rmdir /s out
// cmake --preset x64-debug
// cmake --build out/build/x64-debug
// --------------Create tables---------------
void createTable(std::shared_ptr<IPostgresDB> postgresDB)
{
    // create user table
    auto userTableRes = postgresDB->executeCommand(Queries::CREATE_USER_TABLE);
    if(userTableRes.getMessageCode() == MessageCodes::ERROR_M)
    {
        std::cerr<<userTableRes.getMessage()<<std::endl;
    }
    else
    {
        std::cout<<"Successfully created User table"<<std::endl;
    }

    auto otpTableRes = postgresDB->executeCommand(Queries::CREATE_OTP_TABLE);
    if(otpTableRes.getMessageCode() == MessageCodes::ERROR_M)
    {
        std::cerr<<otpTableRes.getMessage()<<std::endl;
    }
    else
    {
        std::cout<<"Successfully created OTP table"<<std::endl;
    }
}

void loadEnv(const std::string& file) {
    std::ifstream f(file);
    std::string line;

    while (std::getline(f, line)) {
        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        _putenv_s(key.c_str(), value.c_str());
    }
}
int main()
{
    // Load env
    loadEnv("C:/Users/Rijul Kansal/OneDrive/Desktop/Auth System/.env");
    std::shared_ptr<IPostgresDB> postgresDB = std::make_shared<PostgresDB>();

    auto makeConnRes = postgresDB->makeConnection();

    if(makeConnRes.getMessageCode() == MessageCodes::ERROR_M)
    {
        std::cerr<<makeConnRes.getMessage()<<std::endl;
    }

    std::cout<<"Successfully connected"<<std::endl;

    createTable(postgresDB);

    // password Validator
    std::unique_ptr<IPasswordValidator> passValidator = std::make_unique<PasswordValidator>();
    // Hash
    std::unique_ptr<IHash> hash = std::make_unique<Hash>();

    // User
    auto userRepo = std::make_shared<UserRepo>(postgresDB);
    std::shared_ptr<IUserReadQuery> userReadQuery = userRepo;
    std::shared_ptr<IUserWriteQuery> userWriteQuery = userRepo;
    std::shared_ptr<IUserController> userController = std::make_shared<UserController>(
                                                                        std::move(passValidator),
                                                                        std::move(hash),
                                                                        userReadQuery,
                                                                        userWriteQuery);
    // Curl
    std::shared_ptr<IAPI> curlApi = std::make_shared<API>();
    
    // Random class
    std::shared_ptr<IRandomNumberGenerator> randomNumGen = std::make_shared<RandomNumberGenerator>();
    
    // Email template
    std::shared_ptr<IEmailTemplate> emailTemplate = std::make_shared<EmailTemplate>();
    // OTP Service
    std::unique_ptr<IOTPService> otpService = std::make_unique<OTPService>(curlApi,randomNumGen,emailTemplate);

    // Orchestration
    std::unique_ptr<IAuthentication> auth = std::make_unique<Authentication>(userController , 
                                                                            std::move(otpService));

    // UI
    auto ui = std::make_unique<UI>(std::move(auth));
    ui->start();

    return 0;
}