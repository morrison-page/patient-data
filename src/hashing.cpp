#include <functional>
#include "hashing.h"

using namespace std;

inline size_t Hashing::hashPassword(const string& password)
{
	hash<string> strHash;
	size_t hashedPassword = strHash(password);

	return hashedPassword;
}

inline bool Hashing::verifyPassword(const string& password, size_t dbHashedPassword)
{
	size_t hashedPassword = hashPassword(password);

	if (hashedPassword == dbHashedPassword)
	{
		return true;
	}

	return false;
};