#pragma once
#include <string>
#include "accessLevel.h"

using namespace std;

class User
{
public:
	// Constructor
	User(string username, size_t password, AccessLevel accessLevel);

	// Class Functions
	string getUsername() const;
	size_t getPassword() const;
	AccessLevel getAccessLevel() const;

protected:
	// Class Properties
	string username;
	size_t password;
	AccessLevel accessLevel;
};