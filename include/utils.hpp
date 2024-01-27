#pragma once

using namespace std;

class Utils
{
public:
	static string accessLevelToString(AccessLevel accessLevel);
	static AccessLevel checkPermissions();
	static string checkPasswordMatch();
};

