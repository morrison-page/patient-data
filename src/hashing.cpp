#include <functional>
#include "hashing.hpp"

using namespace std;

size_t Hashing::hashPassword(const string& password)
{
	hash<string> strHash;
	size_t hashedPassword = strHash(password);

	return hashedPassword;
}

bool Hashing::verifyPassword(const string& password, size_t dbHashedPassword)
{
	size_t hashedPassword = hashPassword(password);

	if (hashedPassword == dbHashedPassword)
	{
		return true;
	}

	return false;
};