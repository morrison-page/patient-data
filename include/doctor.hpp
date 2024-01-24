#pragma once
#include "user.hpp"

using namespace std;

class Doctor : public User {
public:
    // Constructor
    Doctor();

    // Getters and Setters
    int getUserId() const;
    string getUsername() const;
    AccessLevel getAccessLevel() const;

private:
    int userId;
    string username;
};