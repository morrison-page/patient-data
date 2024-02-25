#pragma once

using namespace std;

class Utils
{
public:
	// Class Functions
	static string accessLevelToString(AccessLevel accessLevel);
	static AccessLevel stringToAccessLevel(string accessLevel);
	static AccessLevel checkPermissions(AccessLevel accessLevel);
	static string treatmentStartDate();
	static string treatmentEndDate(int length);
	static string checkPasswordMatch();
};

