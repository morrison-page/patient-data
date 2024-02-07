#include "patient.hpp"
#include "user.hpp"

using namespace std;

// Constructors

Patient::Patient(const string& username, const size_t& hashedPassword, const string& firstname,
	const string& lastname, const bool cancer, const int cancerStage, 
	const bool diabetes, const int diabetesType, const bool smoker, const int smokingQuantity, 
	const bool previouslyCancerous, const bool previouslySmoked) : 
	User(username, hashedPassword, AccessLevel::PATIENT),
	firstname(firstname), lastname(lastname), cancer(cancer), cancerStage(cancerStage),
	diabetes(diabetes), diabetesType(diabetesType), smoker(smoker),
	smokingQuantity(smokingQuantity), previouslyCancerous(previouslyCancerous),
	previouslySmoked(previouslySmoked) { };

Patient::Patient(const int patientId, const string& username, const string& firstname,
	const string& lastname, bool cancer, int cancerStage,
	const bool diabetes, const int diabetesType, const bool smoker, const int smokingQuantity,
	const bool previouslyCancerous, const bool previouslySmoked) :
	User(userId, username, AccessLevel::PATIENT), patientId(patientId),
	firstname(firstname), lastname(lastname), cancer(cancer), cancerStage(cancerStage),
	diabetes(diabetes), diabetesType(diabetesType), smoker(smoker),
	smokingQuantity(smokingQuantity), previouslyCancerous(previouslyCancerous),
	previouslySmoked(previouslySmoked) { };

// Getters and Setters
int Patient::getPatientId() const { return patientId; }
string Patient::getFirstname() const { return firstname; }
string Patient::getLastname() const { return lastname; }
bool Patient::getCancer() const { return cancer; }
int Patient::getCancerStage() const { return cancerStage; }
bool Patient::getDiabetes() const { return diabetes; }
int Patient::getDiabetesType() const { return diabetesType; }
bool Patient::getSmoker() const { return smoker; }
int Patient::getSmokingQuantity() const { return smokingQuantity; }
bool Patient::getPreviouslyCancerous() const { return previouslyCancerous; }
bool Patient::getPreviouslySmoked() const { return previouslySmoked; }

// Class Functions
