#include <iostream>
#include <chrono>
#include <ctime>
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

string Utils::treatmentStartDate()
{
    // Get the current time point
    auto now = chrono::system_clock::now();

    // Convert the current time point to a time_t
    time_t currentTime = chrono::system_clock::to_time_t(now);

    // Convert time_t to std::tm (local time)
    tm localTime;
    if (localtime_s(&localTime, &currentTime) != 0) {
        cerr << "Error converting time." << endl;
    }

    // Store the current date in MySQL format
    char startDate[11]; // YYYY-MM-DD plus null terminator
    sprintf_s(startDate, sizeof(startDate), "%04d-%02d-%02d", localTime.tm_year + 1900, localTime.tm_mon + 1, localTime.tm_mday);

    // Add 6 months
    localTime.tm_mon += 6;

    // Normalize the date (handles cases where adding months results in a change of year)
    mktime(&localTime);

    return startDate;
}

string Utils::treatmentEndDate(int length)
{
    // Get the current time point
    auto now = chrono::system_clock::now();

    // Convert the current time point to a time_t
    time_t currentTime = chrono::system_clock::to_time_t(now);

    // Convert time_t to std::tm (local time)
    tm localTime;
    if (localtime_s(&localTime, &currentTime) != 0) {
        cerr << "Error converting time." << endl;
    }

    // Store the current date in MySQL format
    char startDate[11]; // YYYY-MM-DD plus null terminator
    sprintf_s(startDate, sizeof(startDate), "%04d-%02d-%02d", localTime.tm_year + 1900, localTime.tm_mon + 1, localTime.tm_mday);

    // Add 6 months
    localTime.tm_mon += 6;

    // Normalize the date (handles cases where adding months results in a change of year)
    mktime(&localTime);

    // Store the date 6 months from now in MySQL format
    char endDate[11]; // YYYY-MM-DD plus null terminator
    sprintf_s(endDate, sizeof(endDate), "%04d-%02d-%02d", localTime.tm_year + 1900, localTime.tm_mon + 1, localTime.tm_mday);

    return endDate;
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