#include <iostream>
#include "accessLevel.hpp"
#include "utils.hpp"

using namespace std;

string Utils::accessLevelToString(AccessLevel accessLevel)
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


/*
// TODO: Complete These functions for later
AccessLevel Utils::checkPermissions(string accessLevel)
{
    if (accessLevel == "PATIENT") { return accessLevelToString(accessLevel); }
    if (accessLevel == "DOCTOR") { return accessLevelToString(accessLevel); }
    if (accessLevel == "PHARMACIST") { return accessLevelToString(accessLevel); }
    if (accessLevel == "UNKOWN") { return accessLevelToString(accessLevel); }
}
AccessLevel Utils::checkPermissions(AccessLevel accessLevel)
{
    if (accessLevel == PATIENT) { return accessLevel; }
    if (accessLevel == DOCTOR) { return accessLevel; }
    if (accessLevel == PHARMACIST) { return accessLevel; }
    if (accessLevel == UNKOWN) { return accessLevel; }
}
*/

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