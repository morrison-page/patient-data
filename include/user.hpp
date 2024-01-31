#pragma once
#include <string>
#include "accessLevel.hpp"

using namespace std;

class User
{
public:
	// Constructor
	User(string username, size_t password, AccessLevel accessLevel);

	User(string username, AccessLevel accessLevel);

	// Class Functions

	// Getters
	string getUsername() const;
	size_t getPassword() const;
	AccessLevel getAccessLevel() const;

protected:
	// Class Properties
	int userId;
	string username;
	size_t password;
	AccessLevel accessLevel;
};