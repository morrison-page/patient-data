#include "database.hpp"
#include "patient.hpp"
#include "user.hpp"

using namespace std;

Patient::Patient(const string& username, size_t hashedPassword, const string& firstname,
	const string& lastname, bool cancer, int cancerStage, 
	bool diabetes, int diabetesType, bool smoker, int smokingQuantity, 
	bool previouslyCancerous, bool previouslySmoked) : 
	User(username, hashedPassword, AccessLevel::PATIENT),
	firstname(firstname), lastname(lastname), cancer(cancer), cancerStage(cancerStage),
	diabetes(diabetes), diabetesType(diabetesType), smoker(smoker),
	smokingQuantity(smokingQuantity), previouslyCancerous(previouslyCancerous),
	previouslySmoked(previouslySmoked) { };

// Getters and Setters
string Patient::getFirstname() const { return firstname; }
string Patient::getLastname() const { return lastname; }
bool Patient::getCancer() const { return cancer; }
int Patient::getCancerStage() const { return cancerStage; }
bool Patient::getDiabetes() const { return diabetes; }
int Patient::getDiabetesType() const { return diabetesType; }
bool Patient::getSmoker() const { return smoker; }
int Patient::getSmokingQuantity() const { return smokingQuantity; }
bool Patient::getPreviouslyCancerous() const { return previouslyCancerous; }
bool Patient::getPreviouslySmoked() const { return previouslySmoked;