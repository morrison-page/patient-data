#include "user.h"

using namespace std;

User::User(string username, size_t password, AccessLevel accessLevel) 
	: username(username), password(password), accessLevel(accessLevel) {}

string User::getUsername() const 
{

	return username;
}

size_t User::getPassword() const 
{
	return password; 
}

AccessLevel User::getAccessLevel() const 
{ 
	return accessLevel; 
}