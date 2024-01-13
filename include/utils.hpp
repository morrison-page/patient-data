#pragma once

#include "accessLevel.hpp"

using namespace std;

class Utils
{
public:
	static inline string accessLevelToString(AccessLevel accessLevel);
	static string checkPasswordMatch();
};

