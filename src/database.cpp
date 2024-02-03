#include <iostream>

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>

#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "pharmacist.hpp"
#include "database.hpp"
#include "hashing.hpp"
#include "patient.hpp"
#include "doctor.hpp"
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
            "user_id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,"
            "username VARCHAR(255) NOT NULL,"
            "password BIGINT(255) NOT NULL,"
            "access_level ENUM('PATIENT', 'DOCTOR', 'NURSE', 'PHARMACIST') NOT NULL"
            ");";

        const string createPatientsTable = "CREATE TABLE IF NOT EXISTS patients ("
            "patient_id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,"
            "user_id INT NOT NULL,"
            "first_name VARCHAR(255) NOT NULL,"
            "last_name VARCHAR(255) NOT NULL,"
            "previously_cancerous BOOLEAN NOT NULL,"
            "previously_smoked BOOLEAN NOT NULL,"
            "FOREIGN KEY(user_id) REFERENCES users(user_id)"
            ");";

        const string createCancerTable = "CREATE TABLE IF NOT EXISTS cancer ("
            "cancer_id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,"
            "patient_id INT NOT NULL,"
            "cancer_stage INT NOT NULL,"
            "FOREIGN KEY(patient_id) REFERENCES patients(patient_id)"
            ");";

        const string createDiabetesTable = "CREATE TABLE IF NOT EXISTS diabetes ("
            "diabetes_id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,"
            "patient_id INT NOT NULL,"
            "diabetes_type INT,"
            "FOREIGN KEY(patient_id) REFERENCES patients(patient_id)"
            ");";

        const string createSmokingTable = "CREATE TABLE IF NOT EXISTS smoking ("
            "smoking_id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,"
            "patient_id INT NOT NULL,"
            "pack_frequency VARCHAR(255) NOT NULL,"
            "FOREIGN KEY(patient_id) REFERENCES patients(patient_id)"
            ");";

        const string createTreatmentsTable = "CREATE TABLE IF NOT EXISTS treatments ("
            "treatment_id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,"
            "medical_condition VARCHAR(255) NOT NULL,"
            "treatment VARCHAR(255) NOT NULL,"
            "frequency VARCHAR(255) NOT NULL,"
            "cost FLOAT NOT NULL,"
            "length VARCHAR(255) NOT NULL"
            ");";
        
        const string createTreatmentsTableData = "INSERT INTO treatments ("
            "medical_condition, treatment, frequency, cost, length)"
            "VALUES"
            "('Diabetes (type 1)', 'Insulin', '2 shots per day', 7.52, 'Forever'),"
            "('Diabetes (type 2)', 'Insulin', '1 shot per day', 7.52, 'Forever'),"
            "('Lung Cancer (type 1)', 'Chemotherapy', 'Once every 4 weeks', 10000, 'For 6 months'),"
            "('Lung Cancer (type 2)', 'Chemotherapy', 'Once every 2 weeks', 10000, 'For 6 months'),"
            "('Lung Cancer (type 3)', 'Chemotherapy', 'Once every week', 10000, 'For 12 months'),"
            "('Lung Cancer (type 4)', 'Terminal', 'None', 0, 'Never'),"
            "('Smoking (1 pack per month)', 'Nicotine Tablets', '1 100mg pill a day', 5.63, 'For 6 months'),"
            "('Smoking (1 pack per week)', 'Nicotine Tablets', '2 500mg pill a day', 5.63, 'For 12 months'),"
            "('Smoking (1 pack per day)', 'Nicotine Patches', 'One every 24 hours', 3.64, 'For 2 years');";

        const string createPatientTreatmentsTable = "CREATE TABLE IF NOT EXISTS patient_treatments ("
            "patient_treatment_id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,"
            "patient_id INT NOT NULL,"
            "treatment_id INT NOT NULL,"
            "start_date DATE NOT NULL,"
            "end_date DATE NOT NULL,"
            "FOREIGN KEY(treatment_id) REFERENCES treatments(treatment_id),"
            "FOREIGN KEY(patient_id) REFERENCES patients(patient_id)"
            ");";

        // Exec all SQL to create tables
        exception(createUsersTable);
        exception(createPatientsTable);
        exception(createCancerTable);
        exception(createDiabetesTable);
        exception(createSmokingTable);
        exception(createTreatmentsTable);
        exception(createTreatmentsTableData);
        exception(createPatientTreatmentsTable);

        return true;
    }
 
    return false;
};

// User Creation

// TODO: Insert in treatment(s)
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
    return false;
}

bool Database::createDoctor(const Doctor& doctor)
{
    if (connect())
    {
        // Insert patient data into user table
        pstmt = conn->prepareStatement("INSERT INTO users ("
            "username, password, access_level)"
            "VALUES (?, ?, ?);");
        pstmt->setString(1, doctor.getUsername());
        pstmt->setInt64(2, doctor.getPassword());
        pstmt->setString(3, Utils::accessLevelToString(doctor.getAccessLevel()));
        pstmt->executeUpdate();
        // TODO: Validate Return Value
        return true;
    }
    return false;
}

bool Database::createPharmacist(const Pharmacist& pharmacist)
{
    // Insert patient data into user table
    pstmt = conn->prepareStatement("INSERT INTO users ("
        "username, password, access_level)"
        "VALUES (?, ?, ?);");
    pstmt->setString(1, pharmacist.getUsername());
    pstmt->setInt64(2, pharmacist.getPassword());
    pstmt->setString(3, Utils::accessLevelToString(pharmacist.getAccessLevel()));
    pstmt->executeUpdate();
    // TODO: Validate Return Value
    return true;
}

// Authentication

int Database::authenticateUser()
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
            pstmt = conn->prepareStatement("SELECT * FROM users WHERE username = ?;");
            pstmt->setString(1, username);
            res = pstmt->executeQuery();
            if (res->next())
            {
                int userId = res->getInt(1);
                string dbUsername = res->getString(2);
                size_t dbHashedPassword = res->getInt64(3);
                string accessLevel = res->getString(4);
                if (username == dbUsername && hashedPassword == dbHashedPassword)
                {
                    // TODO: create a user object with all info / find a way to use global uid
                    // TODO: check access level
                    if (accessLevel == "PATIENT") 
                    {
                        return userId;
                    }
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
            return -1;
        }
    }
}

Patient Database::initialisePatient(int userId)
{
    if (connect())
    {
        pstmt = conn->prepareStatement("SELECT * FROM users WHERE userId = ?;");
        pstmt->setInt(1, userId);
        res = pstmt->executeQuery();
        if (res->next())
        {
            int userId = res->getInt(1);
            string username = res->getString(2);
            AccessLevel accessLevel = Utils::stringToAccessLevel(res->getString(3));
           
            pstmt = conn->prepareStatement("SELECT * FROM patients WHERE userId = ?;");
            pstmt->setInt(1, userId);
            res = pstmt->executeQuery();

            if (res->next())
            {
                int patientId = res->getInt(1);
                string firstname = res->getString(1);
                string lastname = res->getString(2);
                bool previouslyCancerous = res->getBoolean(1);
                bool previouslySmoked = res->getBoolean(2);

                pstmt = conn->prepareStatement("SELECT * FROM cancer WHERE patient_id = ?;");
                pstmt->setInt(1, patientId);
                res = pstmt->executeQuery();

                if (res->next())
                {
                    int cancerStage = res->getInt(3);
                    bool cancer = true;

                    pstmt = conn->prepareStatement("SELECT * FROM diabetes WHERE patient_id = ?;");
                    pstmt->setInt(1, patientId);
                    res = pstmt->executeQuery();

                    if (res->next())
                    {
                        int diabetesType = res->getInt(3);
                        bool diabetes = true;

                        pstmt = conn->prepareStatement("SELECT * FROM smoking WHERE patient_id = ?;");
                        pstmt->setInt(1, patientId);
                        res = pstmt->executeQuery();

                        if (res->next())
                        {
                            int smokingQuantity = res->getInt(3);
                            bool smoker = true;

                            // TODO: Redefine Patient constructor w overload
                            Patient Patient(username, firstname, lastname,
                                cancer, cancerStage,
                                diabetes, diabetesType,
                                smoker, smokingQuantity,
                                previouslyCancerous, previouslySmoked);
                            
                            return Patient;
                        }
                    }
                }
            }
        }
    }
};

/*
Doctor Database::initialiseDoctor(int userId)
{
    pstmt = conn->prepareStatement("SELECT * FROM users WHERE userId = ?;");
    pstmt->setInt(1, userId);
    res = pstmt->executeQuery();
    if (res->next())
    {
        // TODO: Check user perms
        int userId = res->getInt(1);
        string username = res->getString(2);
        AccessLevel accessLevel;

        pstmt = conn->prepareStatement("SELECT * FROM patients WHERE userId = ?;");
        pstmt->setInt(1, userId);
        res = pstmt->executeQuery();
    }
}

Pharmacist Database::initialisePharmacist(int userId)
{
    pstmt = conn->prepareStatement("SELECT * FROM users WHERE userId = ?;");
    pstmt->setInt(1, userId);
    res = pstmt->executeQuery();
    if (res->next())
    {
        // TODO: Check user perms
        int userId = res->getInt(1);
        string username = res->getString(2);
        AccessLevel accessLevel;

        pstmt = conn->prepareStatement("SELECT * FROM patients WHERE userId = ?;");
        pstmt->setInt(1, userId);
        res = pstmt->executeQuery();
    }
}
*/

// Utility Functions

void Database::exception(const string query)
{
    connect();

    stmt = conn->createStatement();

    try {
		stmt->execute(query);
	}
    catch (sql::SQLException& e) {
        cerr << "# ERR: SQLException in " << __FILE__ << endl;
		cerr << "# ERR: " << e.what() << endl;
		cerr << " (MySQL error code: " << e.getErrorCode();
		cerr << ", SQLState: " << e.getSQLState() << ")" << endl << endl;
	}
};