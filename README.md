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
                                ┌──────────────┐
                                │    Start     │
                                └──────┬───────┘
                                       │
                                       ▼
                    ┌─────────────────────────────────┐
                    │ Please enter one option below   │
                    │ 1 for SignUp                    │
                    │ 2 for Login                     │
                    └──────────────┬──────────────────┘
                                   │
                 ┌─────────────────┴─────────────────┐
                 │                                   │
                 ▼                                   ▼

        ┌──────────────────┐              ┌──────────────────┐
        │      Signup      │              │      Login       │
        └────────┬─────────┘              └────────┬─────────┘
                 │                                 │
                 ▼                                 ▼

      ┌─────────────────────┐        ┌─────────────────────────┐
      │ Enter Username      │        │ Press 1 for Login       │
      │ Enter Email         │        │ Press 2 Forgot Password │
      │ Enter Password      │        │ Press 3 Go Back         │
      └─────────┬───────────┘        └──────────┬──────────────┘
                │                               │
                ▼                               │
      ┌─────────────────────┐                   │
      │ Validate Password   │                   │
      │ - Uppercase         │                   │
      │ - Lowercase         │                   │
      │ - Digit             │                   │
      │ - Special Character │                   │
      │ - Minimum Length    │                   │
      └─────────┬───────────┘                   │
                │                               │
                ▼                               │
      ┌─────────────────────┐                   │
      │ Signup Successful   │                   │
      │ Redirect to Login   │                   │
      └─────────┬───────────┘                   │
                │                               │
                └──────────────┐                │
                               ▼                ▼
                 ┌────────────────────────────┐
                 │ Enter Email and Password   │
                 └────────────┬───────────────┘
                              │
                              ▼
                    ┌──────────────────────┐
                    │ Password Correct ?   │
                    └──────────┬───────────┘
                               │
                 ┌─────────────┴─────────────┐
                 │                           │
                 ▼                           ▼
       ┌──────────────────┐      ┌──────────────────────┐
       │ Login Successful │      │ Password Incorrect   │
       └──────────────────┘      └──────────┬───────────┘
                                            │
                                            ▼
                              ┌─────────────────────────┐
                              │ Forgot Password Flow    │
                              └──────────┬──────────────┘
                                         │
                                         ▼

                              ┌─────────────────────────┐
                              │ Enter Registered Email  │
                              └──────────┬──────────────┘
                                         │
                                         ▼
                              ┌─────────────────────────┐
                              │ Generate 6 Digit OTP    │
                              │ Send OTP via Email      │
                              └──────────┬──────────────┘
                                         │
                                         ▼
                              ┌─────────────────────────┐
                              │ Enter OTP               │
                              └──────────┬──────────────┘
                                         │
                                         ▼
                              ┌─────────────────────────┐
                              │ OTP Valid ?             │
                              └──────────┬──────────────┘
                                         │
                          ┌──────────────┴──────────────┐
                          │                             │
                          ▼                             ▼
               ┌────────────────────┐      ┌──────────────────┐
               │ Enter New Password │      │ Invalid OTP      │
               └─────────┬──────────┘      └──────────────────┘
                         │
                         ▼
               ┌────────────────────┐
               │ Update Password    │
               └─────────┬──────────┘
                         │
                         ▼
               ┌────────────────────┐
               │ Password Changed   │
               │ Successfully       │
               └─────────┬──────────┘
                         │
                         ▼
               ┌────────────────────┐
               │ Redirect to Login  │
               └─────────┬──────────┘
                         │
                         ▼
               ┌────────────────────┐
               │ Login with New     │
               │ Password           │
               └─────────┬──────────┘
                         │
                         ▼
               ┌────────────────────┐
               │ Login Successful   │
               └────────────────────┘
