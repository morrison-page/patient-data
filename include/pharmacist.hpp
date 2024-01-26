#pragma once
#include "user.hpp"

using namespace std;

class Pharmacist : public User {
public:
    // Constructor
    Pharmacist();

    // Getters and Setters
    int getUserId() const;
private:
    int userId;
    string username;
};