#include "user.h"

using namespace std;

User::User(std::string username, std::string password, AccessLevel accessLevel) 
	: username(username), password(password), accessLevel(accessLevel) {}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
AccessLevel User::getAccessLevel() const { return accessLevel; }