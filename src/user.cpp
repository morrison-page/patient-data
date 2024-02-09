#include "user.hpp"

using namespace std;

User::User(string username, size_t password, AccessLevel accessLevel) 
	: username(username), password(password), accessLevel(accessLevel) {}

User::User(int userId, string username, AccessLevel accessLevel)
	: userId(userId), username(username), accessLevel(accessLevel) {}

// Getters

int User::getUserId() const { return userId; }
string User::getUsername() const { return username; }
size_t User::getPassword() const { return password; }
AccessLevel User::getAccessLevel() const { return accessLevel; }