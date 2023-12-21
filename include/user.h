#pragma once
#include <string>
#include "accessLevel.h"

using namespace std;

class User
{
public:
	// Constructor
	User(string username, string password, AccessLevel accessLevel);

	// Class Functions
	string getUsername() const;
	string getPassword() const;
	AccessLevel getAccessLevel() const;

private:
	// Class Properties
	string username;
	string password;
	AccessLevel accessLevel;
};