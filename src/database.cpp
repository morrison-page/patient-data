#include <iostream>

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>

#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "database.hpp"

using namespace std;

// Constructor
Database::Database()
{
    createDatabase();
};
// Destructor
Database::~Database()
{
    delete stmt;
    delete conn;
    delete pstmt;
};


// Class Functions

inline bool Database::connect()
{
	// Grab Database Driver and Connect
	driver = sql::mysql::get_driver_instance();
	conn = driver->connect(server, username, password);

    // Use this database for query exec
    conn->setSchema("ws344889_patient_data");

	// Return Connection status
	return conn;
};

bool Database::createDatabase()
{
    if (connect())
    {
        // Create statement Obj
        stmt = conn->createStatement();

        // SQL statements to create tables
        const string createUsersTable = "CREATE TABLE IF NOT EXISTS users ("
            "user_id INT PRIMARY KEY AUTO_INCREMENT,"
            "username VARCHAR(255) NOT NULL,"
            "password VARCHAR(255) NOT NULL"
            ");";

        const string createRolesTable = "CREATE TABLE IF NOT EXISTS roles ("
            "role_id INT PRIMARY KEY,"
            "role_name VARCHAR(255) NOT NULL"
            ");";

        const string createRolesData = "INSERT IGNORE INTO roles (role_id, role_name) VALUES (1, 'patient'), (2, 'doctor'), (3, 'pharmacist');";

        const string createUserRolesTable = "CREATE TABLE IF NOT EXISTS user_roles ("
            "user_id INT NOT NULL,"
            "role_id INT NOT NULL,"
            "PRIMARY KEY(user_id, role_id),"
            "FOREIGN KEY(user_id) REFERENCES users(user_id),"
            "FOREIGN KEY(role_id) REFERENCES roles(role_id)"
            ");";

        const string createPatientsTable = "CREATE TABLE IF NOT EXISTS patients ("
            "patient_id INT PRIMARY KEY AUTO_INCREMENT,"
            "user_id INT NOT NULL,"
            "first_name VARCHAR(255) NOT NULL,"
            "last_name VARCHAR(255) NOT NULL,"
            "previously_cancerous BOOLEAN NOT NULL,"
            "previously_smoked BOOLEAN NOT NULL,"
            "FOREIGN KEY(user_id) REFERENCES users(user_id)"
            ");";

        const string createCancerTable = "CREATE TABLE IF NOT EXISTS cancer ("
            "cancer_id INT PRIMARY KEY AUTO_INCREMENT,"
            "patient_id INT NOT NULL,"
            "cancer_stage INT NOT NULL,"
            "FOREIGN KEY(patient_id) REFERENCES patients(patient_id)"
            ");";

        const string createDiabetesTable = "CREATE TABLE IF NOT EXISTS diabetes ("
            "diabetes_id INT PRIMARY KEY AUTO_INCREMENT,"
            "patient_id INT NOT NULL,"
            "diabetes_type INT,"
            "FOREIGN KEY(patient_id) REFERENCES patients(patient_id)"
            ");";

        const string createSmokingTable = "CREATE TABLE IF NOT EXISTS smoking ("
            "smoking_id INT PRIMARY KEY AUTO_INCREMENT,"
            "patient_id INT NOT NULL,"
            "pack_frequency VARCHAR(255),"
            "FOREIGN KEY(patient_id) REFERENCES patients(patient_id)"
            ");";

        // Exec all SQL to create tables
        exception(createUsersTable);
        exception(createRolesTable);
        exception(createRolesData);
        exception(createUserRolesTable);
        exception(createPatientsTable);
        exception(createCancerTable);
        exception(createDiabetesTable);
        exception(createSmokingTable);

        return true;
    }
 
    return false;
};

// User Creation

bool Database::createPatient(const Patient& patient)
{
    if (connect())
    {
        // Insert patient data into user table
        pstmt = conn->prepareStatement("INSERT INTO users ("
            "username, password)"
            "VALUES (?,?);");
        pstmt->setString(1,patient.getUsername());
        pstmt->setInt64(2, patient.getPassword());
        pstmt->executeUpdate();
        // Grab auto generated user id
        stmt = conn->createStatement();
        res = stmt->executeQuery("SELECT LAST_INSERT_ID();");
        if (res->next())
        {
            // Insert patient data into patients table
            int userId = res->getInt(1);
            pstmt = conn->prepareStatement("INSERT INTO patients ("
                "user_id, first_name, last_name,"
                "previously_cancerous, previously_smoked)"
                "VALUES (? , ? , ? , ? , ?)");
            pstmt->setInt(1, userId);
            pstmt->setString(2, patient.getFirstname());
            pstmt->setString(3, patient.getLastname());
            pstmt->setBoolean(4, patient.getPreviouslyCancerous());
            pstmt->setBoolean(5, patient.getPreviouslySmoked());
            pstmt->executeUpdate();
            
            // TODO: Insert data into cancer, diabetes, smoking and user_roles
        }
    }
}

// Utility Functions

void Database::exception(const string query)
{
    connect();

    // Create statement Obj
    stmt = conn->createStatement();

    try {
		stmt->execute(query);
	}
    catch (sql::SQLException& e) {
		cerr << "# ERR: SQLException in " << __FILE__;
		cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cerr << "# ERR: " << e.what();
		cerr << " (MySQL error code: " << e.getErrorCode();
		cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
	}
};