#pragma once
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "patient.hpp"
#include "user.hpp"


using namespace std;

class Database
{
public:
	// Constructor & Destructor
	Database();
	~Database();

	// Class Functions

	inline bool connect();
	bool createDatabase();
	void exception(const string query);

	// User Creation
	bool createPatient(const Patient& patient);
	bool createStaff(const User& staff);

	// Authentication
	int authenticateUser();
	Patient initialisePatient(int userId);
	User initialiseStaff(int userId);

	// Data Fetch Functions
	void getPatientTreatments(int patientId);
	void getPatientDetails(int patientId);
	void getPatientCosts(int patientId);

	// Data Update Functions

	void updateCancer(int patientId, const int cancerStage);
	void updateDiabetes(int patientId, const int diabetesType);
	void updateSmoking(int patientId, const int smokingFequency);

	// Data Analytics Functions
	void averageAgeOfCancerPatients();
	void averageAgeOfDiabeticPatients();
	void smokingFrequencyOfCancerPatients();

private:
	// Database Pointer Declaration
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* conn;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;

	// Database Connection Info
	const string server = "plesk.remote.ac";
	const string username = "ws344889_db_user";
	const string password = "1w^9Hcf16";
};