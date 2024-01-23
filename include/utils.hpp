#pragma once

#include "accessLevel.hpp"

using namespace std;

class Utils
{
public:
	static string accessLevelToString(AccessLevel accessLevel);
	static string checkPasswordMatch();
};

