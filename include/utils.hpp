#pragma once

using namespace std;

class Utils
{
public:
	static string accessLevelToString(AccessLevel accessLevel);
	static AccessLevel stringToAccessLevel(string accessLevel);
	static AccessLevel checkPermissions(AccessLevel accessLevel);
	static string checkPasswordMatch();
};

