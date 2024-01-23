#pragma once
#include <string>

using namespace std;

class Hashing
{
public:
    static size_t hashPassword(const string& password);
    static bool verifyPassword(const string& password, size_t hashedPassword);
};