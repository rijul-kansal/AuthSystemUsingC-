#include "UI.h"
#include "Utility/Messages.h"
#include <iostream>
using namespace std;
void UI::start()
{
    cout<<endl;
    while(true)
    {
        cout<<"Please enter one option below"<<endl;
        cout<<"1 for SignUp"<<endl;
        cout<<"2 for Login"<<endl;
        cout<<"3 for Exit"<<endl;
        
        int n ;
        cin>>n;
        cout<<endl;

        if(n==1)
        {
            string username="";
            string email="";
            string password="";

            askingSignUpDetails(username,email,password);
            auto res = auth->signup(username,email,password);

            if(res.getMessageCode() == MessageCodes::ERROR_M)
            {
                cout<<res.getMessage()<<endl;
                continue;
            }
            cout<<"Sign Up successfully,Please verify now"<<endl;
            cout<<""<<endl;
            auto genOTPRes = auth->generateOTP(email);

            if(genOTPRes.getMessageCode() == MessageCodes::ERROR_M)
            {
                cout<<genOTPRes.getMessage()<<endl;
                continue;
            } 
            
            auto validateOTPRes = otpValidation(email);
            if(validateOTPRes.getMessageCode() == MessageCodes::ERROR_M)
            {
                cout<<validateOTPRes.getMessage()<<endl;
                continue;
            }

            auto verifiedRes = auth->isVerifiedTrue(email);
            if(verifiedRes.getMessageCode() == MessageCodes::ERROR_M)
            {
                cout<<validateOTPRes.getMessage()<<endl;
                continue;
            }
            cout<<"OTP validated successfully"<<endl;
        }
        else if(n==2)
        {
            
            cout<<"Press 1 for login"<<endl;
            cout<<"Press 2 for Forget Password"<<endl;
            cout<<"Press 3 for go Back"<<endl;
            
            int x ;
            cin>>x;
            cout<<endl;

            if(x==1)
            {
                string email="";
                string password="";

                askingLoginDetails(email,password);
                auto res = auth->login(email,password);

                if(res.getMessageCode() == MessageCodes::ERROR_M)
                {
                    cout<<res.getMessage()<<endl;
                }
                else
                {
                    cout<<"Login Successfully"<<endl;
                    cout<<""<<endl;
                }
            }
            else if(x==2)
            {
                std::string email;
                askingEmail(email);
                auto res = auth->generateOTP(email);
                
                if(res.getMessageCode() == MessageCodes::ERROR_M)
                {
                    cout<<res.getMessage()<<endl;
                    cout<<endl;
                }
                else
                {
                    std::string otp;
                    askingOTP(otp);
                    
                    auto validateOTPRes = otpValidation(email);
                    if(validateOTPRes.getMessageCode() == MessageCodes::ERROR_M)
                    {
                        cout<<validateOTPRes.getMessage()<<endl;
                        cout<<endl;
                    }
                    else
                    {
                        std::string password;
                        askingPassword(password);
                        auto changePassRes = auth->changePassword(email,password);
                        if(changePassRes.getMessageCode() == MessageCodes::ERROR_M)
                        {
                            cout<<changePassRes.getMessage()<<endl;
                            cout<<endl;
                        }
                        else
                        {
                            cout<<"Password changed Successfully"<<endl;
                            cout<<endl;
                        }
                    }
                }
            }
            else
            {
                continue;
            }
        }
        else
        {
            return;
        }
    }
}

void UI::askingSignUpDetails(std::string &username, std::string &email, std::string &password)
{
    cout<<"Please enter all the details"<<endl;
    while(true)
    {

        if(username.empty())
        {
            cout<<"Username: ";
            cin>>username;
            cout<<endl;
        }    
        
        if(email.empty())
        {
            cout<<"email: ";
            cin>>email;
            cout<<endl;
        }
        
        if(password.empty())
        {
            cout<<"Password should be of length min 6 char with atleast 1 UpperCase 1 Lowercase ";
            cout<<" 1 Digit and 1 special char should be there "<<endl;
            cout<<"password: ";
            cin>>password;
            cout<<endl;
        }
        

        if(username.empty() )
        {
            cout<<"Username is empty Please enter username again"<<endl;
            continue;
        }
        if(email.empty())
        {
            cout<<"Email is empty Please enter email again"<<endl;
            continue;
        }

        if(password.empty())
        {
            cout<<"Password is empty Please enter password again"<<endl;
            continue;
        }

        return;
    }
}

void UI::askingLoginDetails(std::string &email, std::string &password)
{
    cout<<"Please enter all the details"<<endl;
    while(true)
    {

        if(email.empty())
        {
            cout<<"email ";
            cin>>email;
            cout<<endl;
        }
        
        if(password.empty())
        {
            cout<<"password ";
            cin>>password;
            cout<<endl;
        }
        
        if(email.empty())
        {
            cout<<"Email is empty Please enter email again"<<endl;
            continue;
        }

        if(password.empty())
        {
            cout<<"Password is empty Please enter password again"<<endl;
            continue;
        }

        return;
    }
}

void UI::askingEmail(std::string &email)
{
    cout<<"Please enter all the details"<<endl;
    while(true)
    {
        if(email.empty())
        {
            cout<<"email ";
            cin>>email;
            cout<<endl;
        }
        
        if(email.empty())
        {
            cout<<"Email is empty Please enter email again"<<endl;
            continue;
        }
        return;
    }
}

void UI::askingOTP(std::string &otp)
{
    cout<<"Please enter 6 digit otp send to your email address"<<endl;
    while(true)
    {

        if(otp.empty())
        {
            cout<<"OTP ";
            cin>>otp;
            cout<<endl;
        }

        if(otp.empty())
        {
            cout<<"OTP is empty Please enter otp again"<<endl;
            continue;
        }

        return;
    }
}

void UI::askingPassword(std::string &password)
{
    cout<<"Please enter all the details"<<endl;
    while(true)
    {

        if(password.empty())
        {
            cout<<"password ";
            cin>>password;
            cout<<endl;
        }

        if(password.empty())
        {
            cout<<"Password is empty Please enter password again"<<endl;
            continue;
        }

        return;
    }
}

AuthResult UI::otpValidation(const std::string& email)
{
    while(true)
    {
        std::string otp;
        askingOTP(otp);
        auto res = auth->validateOTP(email,otp);
        if(res.getMessageCode() == MessageCodes::ERROR_M)
        {
            if(res.getMessage() == DefaultMessage::OTPWrong)
            {
                cout<<"Wrong OTP enter again"<<endl;
                continue;
            }
        }
        return res;
    }
}
