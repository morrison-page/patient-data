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

AccessLevel Utils::stringToAccessLevel(string accessLevel)
{
    if (accessLevel == "PATIENT") { return AccessLevel::PATIENT; }
    if (accessLevel == "DOCTOR") { return AccessLevel::DOCTOR; }
    if (accessLevel == "PHARMACIST") { return AccessLevel::PHARMACIST; }
    if (accessLevel == "UNKNOWN") { return AccessLevel::UNKNOWN; }
    return AccessLevel::UNKNOWN;
}
AccessLevel Utils::checkPermissions(AccessLevel accessLevel)
{
    if (accessLevel == AccessLevel::PATIENT) { return accessLevel; }
    if (accessLevel == AccessLevel::DOCTOR) { return accessLevel; }
    if (accessLevel == AccessLevel::PHARMACIST) { return accessLevel; }
    if (accessLevel == AccessLevel::UNKNOWN) { return accessLevel; }
    return AccessLevel::UNKNOWN;
}

string Utils::checkPasswordMatch()
{
    while (true)
    {
        string password, passwordCheck;
        cout << "Password: ";
        cin >> password;
        cout << "Password Again: ";
        cin >> passwordCheck;

        if (password != passwordCheck)
        {
            cout << "Passwords do not match. Try Again: \n\n";
            checkPasswordMatch();
        }
        else
        {
            return password;
        }
    }
}