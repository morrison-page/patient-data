#pragma once
#include <string>

using namespace std;

class Hashing
{
public:
    size_t hashPassword(const string& password);
    bool verifyPassword(const string& password, size_t hashedPassword);
};