# Auth System Using C++

A backend authentication system built in modern C++ using PostgreSQL, libcurl, and CMake.
The project focuses on clean architecture, SOLID principles, dependency injection, and modular backend design.

## Features

- User Signup
- User Login
- Forgot Password Flow

## Build

cmake --preset x64-debug
cmake --build --preset x64-debug

## 6. Technologies used

- C++17
- PostgreSQL
- libcurl
- nlohmann/json
- CMake
- vcpkg

## FLOW

```mermaid

    A([Start]) --> B{Choose Option}

    B -->|Sign Up| C[Enter Username, Email, Password]
    B -->|Login| L{Choose Login Option}

    %% SIGNUP FLOW
    C --> D[Send OTP to Email]
    D --> E{OTP Correct?}

    E -->|No| D
    E -->|Yes| F[User Verified]
    F --> G[Redirect to Login Page]

    %% LOGIN MENU
    L -->|Login| M[Enter Email and Password]
    L -->|Forgot Password| FP1[Enter Email Address]

    %% NORMAL LOGIN
    M --> N{Password Correct?}

    N -->|No| O[Show Invalid Credentials]
    N -->|Yes| P{User Verified?}

    P -->|Yes| Q[Login Successful]

    P -->|No| R[Send OTP to Email]
    R --> S{OTP Correct?}

    S -->|No| R
    S -->|Yes| T[User Verified]
    T --> Q

    %% FORGOT PASSWORD FLOW
    FP1 --> FP2[Send OTP to Email]
    FP2 --> FP3{OTP Correct?}

    FP3 -->|No| FP2
    FP3 -->|Yes| FP4[Enter New Password]

    FP4 --> FP5[Password Updated Successfully]
    FP5 --> FP6[Redirect to Login Page]

    Q --> Z([End])
    G --> Z
    FP6 --> Z
```