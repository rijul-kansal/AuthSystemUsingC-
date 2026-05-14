#pragma once

#include <string>
namespace Queries
{
    const std::string CREATE_USER_TABLE = "CREATE TABLE IF NOT EXISTS Users ( "
                                          " user_id SERIAL PRIMARY KEY , "              
                                          " user_name VARCHAR(30) NOT NULL , "              
                                          " email VARCHAR(50) NOT NULL UNIQUE , "              
                                          " is_verified bool DEFAULT false ,"              
                                          " password VARCHAR(100) NOT NULL )";
    
    const std::string INSERT_NEW_USER   = " INSERT INTO Users(user_name,email,password) "
                                          " Values($1,$2,$3)";

    const std::string CHECK_USER        = " SELECT user_name, email , password , is_verified FROM Users "
                                          " where email = $1";
                                          
    const std::string CHANGE_PASSWORD   = " UPDATE Users "
                                          " Set password = $2 "
                                          " where email = $1 ";
    const std::string MAKE_IS_VERIFIED_TRUE = " UPDATE Users "
                                              " set is_verified = true "  
                                              " where email = $1 ";  
    const std::string CREATE_OTP_TABLE = " CREATE TABLE IF NOT EXISTS OTP( "
                                         " otp_id SERIAL PRIMARY KEY , "
                                         " otp VARCHAR(6) NOT NULL , "
                                         " otp_validity BIGINT NOT NULL DEFAULT (EXTRACT(EPOCH FROM NOW())::BIGINT) , "
                                         " email VARCHAR(50) NOT NULL UNIQUE, "
                                         " FOREIGN KEY(email) references Users(email) ON DELETE CASCADE ) ";

    const std::string INSERT_NEW_OTP =   " INSERT INTO OTP(otp,email) "
                                         " Values($1,$2) "
                                         " On Conflict (email) Do UPDATE "
                                         " SET otp = $1 , "
                                         " otp_validity = (EXTRACT(EPOCH FROM NOW())::BIGINT) ";
    
    const std::string DELETE_OTP_WITH_EMAIL =  " DELETE FROM OTP "
                                               " WHERE email = 1$ ";

    const std::string CHECK_USER_OTP_IN_OTP_TABLE = " Select email,otp_validity from OTP "
                                                    " where email = $1 AND otp = $2";
};