#pragma once
#include "user.hpp"

using namespace std;

class Patient : public User {
public:
    // Constructor
    Patient(const string& username, size_t hashedPassword, const string& firstname,
        const string& lastname, bool hasCancer, int cancerStage,
        bool hasDiabetes, int diabetesType, bool isSmoker, int smokingQuantity,
        bool previouslyHadCancer, bool previouslySmoked);

    // Getters and Setters
    string getFirstname() const;
    string getLastname() const;
    bool getCancer() const;
    int getCancerStage() const;
    bool getDiabetes() const;
    int getDiabetesType() const;
    bool getSmoker() const;
    int getSmokingQuantity() const;
    bool getPreviouslyCancerous() const;
    bool getPreviouslySmoked() const;

private:
    string firstname;
    string lastname;
    bool cancer;
    int cancerStage;
    bool diabetes;
    int diabetesType;
    bool smoker;
    int smokingQuantity;
    bool previouslyCancerous;
    bool previouslySmoked;
};