#pragma once
#include <vector>
#include "user.hpp"

using namespace std;

class Patient : public User {
public:
    // Constructors

    Patient(const string& username, const size_t& hashedPassword, const string& firstname,
        const string& lastname, const bool hasCancer, const int cancerStage,
        const bool hasDiabetes, const int diabetesType, const bool isSmoker,
        const int smokingQuantity, const bool previouslyHadCancer,
        const bool previouslySmoked);

    Patient(const int patientId, const string& username, const string& firstname,
        const string& lastname, const bool hasCancer, const int cancerStage,
        const bool hasDiabetes, const int diabetesType, const bool isSmoker, const int smokingQuantity,
        const bool previouslyHadCancer, const bool previouslySmoked);

    // Getters and Setters
    int getPatientId() const;
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
    int patientId;
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