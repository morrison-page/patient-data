#include <iostream>
#include "accessLevel.hpp"
#include "utils.hpp"

using namespace std;

inline string Utils::accessLevelToString(AccessLevel accessLevel)
{
    switch (accessLevel) {
    case AccessLevel::PATIENT:
        return "PATIENT";
    case AccessLevel::DOCTOR:
        return "DOCTOR";
    case AccessLevel::PHARMACIST:
        return "PHARMACIST";
    default:
        return "UNKNOWN";
    }
}

string Utils::checkPasswordMatch() 
{
    string password, passwordCheck;
    cout << "Password: ";
    cin >> password;
    cout << "Password Again: ";
    cin >> passwordCheck;

    if (password != passwordCheck)
    {
        cout << "Passwords do not match. Try Again: \n\n";
        Utils::checkPasswordMatch();
    }
    else
    {
        return password;
    }
}