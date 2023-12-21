#include <stdexcept>
#include "userDatabase.h"

using namespace std;

UserDatabase::UserDatabase() {}

void UserDatabase::createPatient(const User& patient) 
{
    users.push_back(patient);
}

void UserDatabase::createDoctor(const User& doctor)
{
    users.push_back(doctor);
}

void UserDatabase::createNurse(const User& nurse)
{
    users.push_back(nurse);
}

void UserDatabase::createPharmacist(const User& pharmacist)
{
    users.push_back(pharmacist);
}

AccessLevel UserDatabase::authenticate(string username, string password) {
    for (const User& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            return user.getAccessLevel();
        }
    }

    throw runtime_error("Invalid username or password");
}