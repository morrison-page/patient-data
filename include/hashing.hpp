#pragma once
#include <string>

using namespace std;

class Hashing
{
public:
    inline static size_t hashPassword(const string& password);
    inline static bool verifyPassword(const string& password, size_t hashedPassword);
};