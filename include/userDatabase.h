#pragma once
#include <vector>
#include "user.h"

class UserDatabase 
{
public:
	// Constructor
	UserDatabase();

	// Class Functions
	void createPatient(const User&);
	void createDoctor(const User&);
	void createNurse(const User&);
	void createPharmacist(const User&);
	AccessLevel authenticate(string username, string password);

private:
	vector<User> users;
};