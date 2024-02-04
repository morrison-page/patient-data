#include <iostream>
#include <chrono>

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

            // Grab Inserted ID that auto increments
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
                        "VALUES (?, ?);");
                    pstmt->setInt(1, patientId);
                    pstmt->setInt(2, patient.getCancerStage());
                    pstmt->executeUpdate();
                    // Insert cancer treatment
                    if (patient.getCancerStage() == 1)
                    {
                        pstmt = conn->prepareStatement("INSERT INTO patient_treatments ("
                        	"patient_id, treatment_id, start_date, end_date)"
                        	"VALUES (?, ?, ?, ?);");
                        pstmt->setInt(1, patientId);
                        pstmt->setInt(2, 3);
                        // Get date rangte for treatment
                        string startDate = Utils::treatmentStartDate();
                        string endDate = Utils::treatmentEndDate(6);
                        pstmt->setString(3, startDate);
                        pstmt->setString(4, endDate);
                        pstmt->executeUpdate();
                    }
                    else if (patient.getCancerStage() == 2)
                    {
                        pstmt = conn->prepareStatement("INSERT INTO patient_treatments ("
                            "patient_id, treatment_id, start_date, end_date)"
                            "VALUES (?, ?, ?, ?);");
                        pstmt->setInt(1, patientId);
                        pstmt->setInt(2, 4);
                        // Get date rangte for treatment
                        string startDate = Utils::treatmentStartDate();
                        string endDate = Utils::treatmentEndDate(6);
                        pstmt->setString(3, startDate);
                        pstmt->setString(4, endDate);
                        pstmt->executeUpdate();
					}
                    else if (patient.getCancerStage() == 3)
                    {
                        pstmt = conn->prepareStatement("INSERT INTO patient_treatments ("
                            "patient_id, treatment_id, start_date, end_date)"
                            "VALUES (?, ?, ?, ?);");
                        pstmt->setInt(1, patientId);
                        pstmt->setInt(2, 5);
                        // Get date rangte for treatment
                        string startDate = Utils::treatmentStartDate();
                        string endDate = Utils::treatmentEndDate(12);
                        pstmt->setString(3, startDate);
                        pstmt->setString(4, endDate);
                        pstmt->executeUpdate();
					}
                    else if (patient.getCancerStage() == 4)
                    {
                        pstmt = conn->prepareStatement("INSERT INTO patient_treatments ("
                            "patient_id, treatment_id, start_date, end_date)"
                            "VALUES (?, ?, ?, ?);");
                        pstmt->setInt(1, patientId);
                        pstmt->setInt(2, 6);
                        // Get date rangte for treatment
                        string startDate = "0000-00-00";
                        string endDate = "0000-00-00";
                        pstmt->setString(3, startDate);
                        pstmt->setString(4, endDate);
                        pstmt->executeUpdate();
					}
                    else
                    {
                        cerr << "Invalid Cancer Stage";
                    }
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
                    // Insert diabetes treatment
                    if (patient.getDiabetesType() == 1)
                    {
                        pstmt = conn->prepareStatement("INSERT INTO patient_treatments ("
                            "patient_id, treatment_id, start_date, end_date)"
                            "VALUES (?, ?, ?, ?);");
						pstmt->setInt(1, patientId);
						pstmt->setInt(2, 1);
						// Get date range for treatment
						string startDate = Utils::treatmentStartDate();
						string endDate = "0000-00-00";
						pstmt->setString(3, startDate);
						pstmt->setString(4, endDate);
						pstmt->executeUpdate();
					}
					else if (patient.getDiabetesType() == 2)
					{
						pstmt = conn->prepareStatement("INSERT INTO patient_treatments ("
                            "patient_id, treatment_id, start_date, end_date)"
                        	"VALUES (?, ?, ?, ?);");
						pstmt->setInt(1, patientId);
						pstmt->setInt(2, 2);
						// Get date range for treatment
						string startDate = Utils::treatmentStartDate();
                        string endDate = "0000-00-00";
						pstmt->setString(3, startDate);
						pstmt->setString(4, endDate);
						pstmt->executeUpdate();
					}
					else
					{
						cerr << "Invalid Diabetes Type";
                    }
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
                    // Insert smoking treatment
                    if (patient.getSmokingQuantity() == 1)
                    {
                        pstmt = conn->prepareStatement("INSERT INTO patient_treatments ("
                            "patient_id, treatment_id, start_date, end_date)"
                            "VALUES (?, ?, ?, ?);");
						pstmt->setInt(1, patientId);
						pstmt->setInt(2, 7);
						// Get date range for treatment
						string startDate = Utils::treatmentStartDate();
						string endDate = Utils::treatmentEndDate(6);
						pstmt->setString(3, startDate);
						pstmt->setString(4, endDate);
						pstmt->executeUpdate();
					}
					else if (patient.getSmokingQuantity() == 2)
					{
						pstmt = conn->prepareStatement("INSERT INTO patient_treatments ("
                            "patient_id, treatment_id, start_date, end_date)"
                        	"VALUES (?, ?, ?, ?);");
						pstmt->setInt(1, patientId);
						pstmt->setInt(2, 8);
						// Get date range for treatment
						string startDate = Utils::treatmentStartDate();
						string endDate = Utils::treatmentEndDate(12);
						pstmt->setString(3, startDate);
						pstmt->setString(4, endDate);
						pstmt->executeUpdate();
					}
					else if (patient.getSmokingQuantity() == 3)
					{
						pstmt = conn->prepareStatement("INSERT INTO patient_treatments ("
                        	"patient_id, treatment_id, start_date, end_date)"
                            "VALUES (?, ?, ?, ?);");
						pstmt->setInt(1, patientId);
						pstmt->setInt(2, 9);
						// Get date range for treatment
						string startDate = Utils::treatmentStartDate();
						string endDate = Utils::treatmentEndDate(24);
						pstmt->setString(3, startDate);
						pstmt->setString(4, endDate);
						pstmt->executeUpdate();
					}
					else
					{
						cerr << "Invalid Smoking Quantity";
                    }
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
                    return userId;
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
        pstmt = conn->prepareStatement("SELECT * FROM users WHERE user_id = ?;");
        pstmt->setInt(1, userId);
        res = pstmt->executeQuery();
        if (res->next())
        {
            int userId = res->getInt(1);
            string username = res->getString(2);
            AccessLevel accessLevel = Utils::stringToAccessLevel(res->getString(3));
           
            pstmt = conn->prepareStatement("SELECT * FROM patients WHERE user_id = ?;");
            pstmt->setInt(1, userId);
            res = pstmt->executeQuery();

            if (res->next())
            {
                int patientId = res->getInt("patient_id");
                string firstname = res->getString("first_name");
                string lastname = res->getString("last_name");
                bool previouslyCancerous = res->getBoolean("previously_cancerous");
                bool previouslySmoked = res->getBoolean("previously_smoked");

                pstmt = conn->prepareStatement("SELECT * FROM cancer WHERE patient_id = ?;");
                pstmt->setInt(1, patientId);
                res = pstmt->executeQuery();

                if (res->next())
                {
                    int cancerStage = res->getInt("cancer_stage");
                    bool cancer = true;

                    pstmt = conn->prepareStatement("SELECT * FROM diabetes WHERE patient_id = ?;");
                    pstmt->setInt(1, patientId);
                    res = pstmt->executeQuery();

                    if (res->next())
                    {
                        int diabetesType = res->getInt("diabetes_type");
                        bool diabetes = true;

                        pstmt = conn->prepareStatement("SELECT * FROM smoking WHERE patient_id = ?;");
                        pstmt->setInt(1, patientId);
                        res = pstmt->executeQuery();

                        if (res->next())
                        {
                            int smokingQuantity = res->getInt("pack_frequency");
                            bool smoker = true;

                            Patient Patient(patientId, username, firstname, lastname,
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

// Data Fetch Functions

void Database::getPatientTreatments(int patientId)
{
    if (connect())
    {
        pstmt = conn->prepareStatement("SELECT t.medical_condition, t.treatment, t.frequency, pt.start_date, pt.end_date "
            "FROM patient_treatments pt "
            "JOIN treatments t ON pt.treatment_id = t.treatment_id "
            "WHERE pt.patient_id = ?;");
        pstmt->setInt(1, patientId);
        res = pstmt->executeQuery();

        while (res->next())
        {
            cout << "Medical Condition: " << res->getString("medical_condition") << endl;
            cout << "Treatment: " << res->getString("treatment") << endl;
            cout << "Frequency: " << res->getString("frequency") << endl;
            cout << "Start Date: " << res->getString("start_date") << endl;
            cout << "End Date: " << res->getString("end_date") << endl << endl;
        }
    }
    else
    {
        cerr << "Failed to connect to the database." << endl;
    }
}

void Database::getPatientDetails(int patientId)
{
    if (connect())
    {
		pstmt = conn->prepareStatement("SELECT p.first_name, p.last_name, p.previously_cancerous, p.previously_smoked, c.cancer_stage, d.diabetes_type, s.pack_frequency "
        	"FROM patients p "
        	"LEFT JOIN cancer c ON p.patient_id = c.patient_id "
        	"LEFT JOIN diabetes d ON p.patient_id = d.patient_id "
        	"LEFT JOIN smoking s ON p.patient_id = s.patient_id "
        	"WHERE p.patient_id = ?;");
		pstmt->setInt(1, patientId);
		res = pstmt->executeQuery();

        if (res->next())
        {
			cout << "First Name: " << res->getString("first_name") << endl;
			cout << "Last Name: " << res->getString("last_name") << endl;
			cout << "Previously Cancerous: " << res->getBoolean("previously_cancerous") << endl;
			cout << "Previously Smoked: " << res->getBoolean("previously_smoked") << endl;
			cout << "Cancer Stage: " << res->getInt("cancer_stage") << endl;
			cout << "Diabetes Type: " << res->getInt("diabetes_type") << endl;
			cout << "Smoking Frequency: " << res->getInt("pack_frequency") << endl << endl;
		}
	}
    else
    {
		cerr << "Failed to connect to the database." << endl;
	}
}

void Database::getPatientCosts(int patientId)
{
    if (connect())
    {
		pstmt = conn->prepareStatement("SELECT pt.start_date, pt.end_date "
            "FROM patient_treatments pt "
        	"WHERE pt.patient_id = ?;");
		pstmt->setInt(1, patientId);
		res = pstmt->executeQuery();
        if (res->next())
        {
            // Calculate Daily Cost

            // Calculate Weekly Cost

            // Calculate Monthly Cost

            // Calculate Yearly Cost
        }
	}
    else
    {
		cerr << "Failed to connect to the database." << endl;
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
        cerr << "# ERR: SQLException in " << __FILE__ << endl;
		cerr << "# ERR: " << e.what() << endl;
		cerr << " (MySQL error code: " << e.getErrorCode();
		cerr << ", SQLState: " << e.getSQLState() << ")" << endl << endl;
	}
};