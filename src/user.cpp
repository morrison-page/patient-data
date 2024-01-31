#include "user.hpp"

using namespace std;

User::User(string username, size_t password, AccessLevel accessLevel) 
	: username(username), password(password), accessLevel(accessLevel) {}

User::User(string username, AccessLevel accessLevel)
	: username(username), accessLevel(accessLevel) {}

// Getters

string User::getUsername() const { return username; }
size_t User::getPassword() const { return password; }
AccessLevel User::getAccessLevel() const { return accessLevel; }