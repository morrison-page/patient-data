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
#include "hashing.hpp"
#include "utils.hpp"

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
            "password BIGINT(255) NOT NULL"
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
            "username, password, access_level)"
            "VALUES (?, ?, ?);");
        pstmt->setString(1,patient.getUsername());
        pstmt->setInt64(2, patient.getPassword());
        pstmt->setString(3, Utils::accessLevelToString(patient.getAccessLevel()));
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

            // Grab Inserted ID that auto incriments
            stmt = conn->createStatement();
            res = stmt->executeQuery("SELECT LAST_INSERT_ID();");
            if (res->next())
            {
                int patientId = res->getInt(1);
                // If they have cancer insert data
                if (patient.getCancer())
                {
                    pstmt = conn->prepareStatement("INSERT INTO cancer ("
                        "patient_id, cancer_stage)"
                        "VALUES (?, ?)");
                    pstmt->setInt(1, patientId);
                    pstmt->setInt(2, patient.getCancerStage());
                    pstmt->executeUpdate();
                }
                // If they have diabetes insert data
                if (patient.getDiabetes())
                {
                    pstmt = conn->prepareStatement("INSERT INTO diabetes ("
                        "patient_id, diabetes_type)"
                        "VALUES (?, ?)");
                    pstmt->setInt(1, patientId);
                    pstmt->setInt(2, patient.getDiabetesType());
                    pstmt->executeUpdate();
                }
                // If they smoke insert data
                if (patient.getSmoker())
                {
                    pstmt = conn->prepareStatement("INSERT INTO smoking ("
                        "patient_id, pack_frequency)"
                        "VALUES (?, ?)");
                    pstmt->setInt(1, patientId);
                    pstmt->setInt(2, patient.getSmokingQuantity());
                    pstmt->executeUpdate();
                }
            }
        }
    }
}

//bool Database::createDoctor(const Doctor& doctor);
//bool Database::createPharmacist(const Pharmacist& pharmacist);

// Authentication

bool Database::authenticateUser()
{
    string username, password;
    while (true)
    {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        size_t hashedPassword = Hashing::hashPassword(password);

        if (connect())
        {
            pstmt = conn->prepareStatement("SELECT * FROM users WHERE username = ?");
            pstmt->setString(1, username);
            res = pstmt->executeQuery();
            if (res->next())
            {
                string dbUsername = res->getString(2);
                size_t dbHashedPassword = res->getInt64(3);
                // If not use reccursion
                if (username == dbUsername && hashedPassword == dbHashedPassword)
                {
                    // TODO: create a user object with all info / find a way to use global uid
                    // TODO: check access level
                    return true;
                }
                else
                {
                    cout << "Username or Password Incorrect. Try Again: \n\n";
                }
            }
            else
            {
                cout << "Username or Password Incorrect. Try Again: \n\n";
            }
        }
        else
        {
            cerr << "Failed to Connect to the Databse :(";
            return false;
        }
    }
}

// Utility Functions

void Database::exception(const string query)
{
    connect();

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