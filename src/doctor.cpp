#pragma once
#include "doctor.hpp"
#include "user.hpp"

using namespace std;

int Doctor::getUserId() const { return userId; }
string Doctor::getUsername() const { return username; }