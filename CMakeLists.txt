cmake_minimum_required(VERSION 3.20)

project(AuthSystem)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(AuthSystem
    src/Curl/API.cpp
    src/TemplateService/EmailTemplate.cpp
    src/OTPService/OTPService.cpp
    src/RandomClass/RandomNumberGenerator.cpp
    src/ExternalLibrary/Bcrypt/bcrypt.cpp
    src/ExternalLibrary/Bcrypt/blowfish.cpp
    src/Postgres/PostgresDB.cpp
    src/PasswordValidator/PasswordValidator.cpp
    src/Hash/Hash.cpp
    src/User/UserRepo.cpp
    src/User/UserController.cpp
    src/Time/Time.cpp
    src/Orchestration/Authentication.cpp
    src/UI/UI.cpp
    src/main.cpp
)

target_include_directories(AuthSystem
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ExternalLibrary/Bcrypt
    C:/vcpkg/installed/x64-windows/include
)

target_link_directories(AuthSystem
    PRIVATE
    C:/vcpkg/installed/x64-windows/lib
)

target_link_libraries(AuthSystem
    PRIVATE
    libpq.lib
    CURL::libcurl
    nlohmann_json::nlohmann_json
)