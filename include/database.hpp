#pragma once
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "pharmacist.hpp"
#include "patient.hpp"
#include "doctor.hpp"

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

	bool createDoctor(const Doctor& doctor);

	bool createPharmacist(const Pharmacist& pharmacist);

	// Authentication

	bool authenticateUser();

	Patient initialisePatient(int userId);
	
	Doctor initialiseDoctor(int userId);
	
	Pharmacist initialisePharmacist(int userId);

	// Data Fetch Functions


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